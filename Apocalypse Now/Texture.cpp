#include "Texture.h"

using namespace Pong;


Texture::Texture()
{
	std::fstream errorfile;
	errorfile.open("errorFile.txt");
	m_texture = nullptr;
}

bool Texture::loadFontTexture(SDL_Renderer* renderer, TTF_Font* t_font,std::string text, SDL_Color textColor)
{
	bool success = true;

	SDL_Surface* surface = TTF_RenderText_Solid(t_font, text.c_str(), textColor);

	if (!surface)
	{
		//Error message
		Pong::errorfile << "Unable to create surface." << SDL_GetError() << std::endl;
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (m_texture == nullptr)
		{
			// Error message
			Pong::errorfile << "Unable to create texture: " << SDL_GetError() << std::endl;
			success = false;
		}
		SDL_FreeSurface(surface);
		surface = nullptr;

		return m_texture != nullptr;

	}
	return success;
}



void Texture::render(SDL_Renderer* t_renderer, int t_x, int t_y,SDL_Rect* clipper)
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

	SDL_RenderCopy(t_renderer, m_texture, clipper, &renderQuad);

}

Texture::~Texture()
{
	// Destructor code.
}
