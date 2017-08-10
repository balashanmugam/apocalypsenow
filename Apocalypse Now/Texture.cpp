#include "Texture.h"

using namespace apocalypsenow;


Texture::Texture()
{
	m_texture = nullptr;
}

int apocalypsenow::Texture::getWidth() const
{
	return m_width;
}

int apocalypsenow::Texture::getHeight() const
{
	return m_height;
}

bool Texture::loadFontTexture(TTF_Font* t_font,std::string text, SDL_Color textColor)
{
	bool success = true;

	SDL_Surface* surface = TTF_RenderText_Solid(t_font, text.c_str(), textColor);

	if (!surface)
	{
		//Error message
		apocalypsenow::errorfile << "Unable to create surface." << SDL_GetError() << std::endl;
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(g_renderer, surface);
		if (m_texture == nullptr)
		{
			// Error message
			apocalypsenow::errorfile << "Unable to create texture: " << SDL_GetError() << std::endl;
			success = false;
		}
		SDL_FreeSurface(surface);
		surface = nullptr;

		return m_texture != nullptr;

	}
	return success;
}

bool apocalypsenow::Texture::loadTexture( std::string t_imagepath)
{
	bool success = true;

	// Frees the texture.
	free();

	//stretch image

	SDL_Texture* newTexture;

	SDL_Surface* loadedSurface;
	loadedSurface = IMG_Load(t_imagepath.c_str());

	if (loadedSurface == nullptr)
	{
		errorfile << "Loading Texture: Unable to load texture." << t_imagepath.c_str() << std::endl;
		success = false;
	}
	else
	{

		// Currently Cyan is the color key.
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));


		//Now create the texture.
		newTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
		
		if (newTexture == nullptr)
		{

			errorfile << "Loading Texture: Failed to create texture from surface. " << std::endl;
			errorfile << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
			m_texture = newTexture;
		}
	}
	SDL_FreeSurface(loadedSurface);



	return success;
}

void apocalypsenow::Texture::setColor(SDL_Color t_color)
{
	SDL_SetTextureColorMod(m_texture, t_color.r, t_color.g, t_color.b);
}



void Texture::render(int t_x, int t_y,SDL_Rect* clipper)
{
	SDL_Rect renderQuad{
		t_x,
		t_y,
		m_width,
		m_height
	};

	if (clipper != nullptr)
	{
		renderQuad.h = clipper->h;
		renderQuad.w = clipper->w;
	}

	SDL_RenderCopy(g_renderer, m_texture, clipper, &renderQuad);

}

Texture::~Texture()
{
	// Destructor code.
}

void apocalypsenow::Texture::free()
{
	// Free only if texture is existing.
	if (m_texture != nullptr)
	{
		m_width = 0;
		m_height = 0;
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}

}

