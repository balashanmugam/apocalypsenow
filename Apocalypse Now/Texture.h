#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Renderer.h"

namespace apocalypsenow 
{

	extern SDL_Renderer* g_renderer;
	extern std::fstream errorfile;

	class Texture
	{
	private:
		//holds the texture
		SDL_Texture* m_texture;
	
		//dimensions of the texture.
		int m_width;
		int m_height;

	public:
		Texture();
		~Texture();
		


		// Clears all the memebers.
		void free();

		// Getters and setters

		int getWidth() const;
		int getHeight() const;

		// Creates a texture of the "Text" and "Text color"
		bool loadFontTexture(TTF_Font* t_font,std::string text, SDL_Color textColor);

		// Load texture from the file of the given path.
		bool loadTexture(std::string t_imagepath);	
		
		// Edit the colors of the texture.
		void setColor(SDL_Color t_color);


		void render(int t_x, int t_y,SDL_Rect* clipper = nullptr);

	};
}

#endif
