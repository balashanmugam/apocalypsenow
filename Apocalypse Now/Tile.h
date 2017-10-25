#pragma once
#ifndef _TILE_H_
#define _TILE_H_
#include "GameManager.h"
namespace apocalypsenow
{
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	// Global constant for tiles.

	const int TILE_WIDTH = 80;
	const int TILE_HEIGHT = 80;
	const int TILE_TYPES = 10;
	const int TILE_TOTAL = 192;

	// These tiles are only for testing purposes.

	const int TILE_RED = 0;
	const int TILE_GREEN = 1;
	const int TILE_BLUE = 2;


	const int TILE_TOPLEFT = 0;
	const int TILE_LEFT = 1;
	const int TILE_BOTLEFT = 2;
	const int TILE_TOP = 3;
	const int TILE_MID = 4;
	const int TILE_BOT = 5;
	const int TILE_TOPRIGHT = 6;
	const int TILE_RIGHT = 7;
	const int TILE_BOTRIGHT = 8;
	const int TILE_BLOCK = 99;

	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;

	class Tile
	{
	private:
		SDL_Rect m_box;
		int m_type;

	public:
		// initalizs the tile
		Tile(int t_x, int t_y,int t_tiletype);

		// renders the tile to the screen
		void render(SDL_Rect& t_camera);
		
		// return the tile type.
		int getType();

		// return the SDL_box
		SDL_Rect getBox();
	};


}


#endif