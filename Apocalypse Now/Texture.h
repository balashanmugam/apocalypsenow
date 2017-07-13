#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Renderer.h"

namespace Pong {
	
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

		// Creates a texture of the "Text" and "Text color"
		bool loadFontTexture(SDL_Renderer* renderer,TTF_Font* t_font,std::string text, SDL_Color textColor);

		void render(SDL_Renderer* t_renderer, int t_x, int t_y,SDL_Rect* clipper = nullptr);

	};
}

#endif
