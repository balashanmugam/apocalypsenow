#pragma once
#ifndef _PROTAGONIST_H_
#define _PROTAGONIST_H_

#include "Renderer.h"

namespace apocalypsenow {

	//extern Tile* tiles[TILE_TYPES];4

	class Texture;
	class Tile;
	class Bullet;


	//bool touchesWall(SDL_Rect box, Tile* tiles[]);

	const int PROT_WALK_TOP = 0;
	const int PROT_WALK_BOT = 1;
	const int PROT_WALK_LEFT = 2;
	const int PROT_WALK_RIGHT = 3;
	
	const int PROT_WALKING_DIRECTION = 4;

	const int PROT_TOTAL_FRAMES = 10;

	const int PROT_WIDTH = 60;
	const int PROT_HEIGHT = 60;

	extern Texture g_protagonistTextureTop;
	extern Texture g_protagonistTextureBot;
	extern Texture g_protagonistTextureLeft;
	extern Texture g_protagonistTextureRight;
	extern SDL_Rect g_protagonistClips[PROT_WALKING_DIRECTION][PROT_TOTAL_FRAMES];

	extern Tile* tiles[192];


	// PROT aka Protagonist.
	class Protagonist
	{
	private:
		std::string m_name;

		int m_velX; // velocity in x direction
		int m_velY; // Velocity in y directed.

		// current frame
		int m_frame;

		//Walking direction.
		int m_direction;

		SDL_Rect m_box;


	public:
		static const int PROT_WIDTH = 50;
		static const int PROT_HEIGHT = 50;

		static const int PROT_SPEED = 2;

		Protagonist();

		Protagonist(int t_x, int tx_y);
		
		//Handle events 
		void handleEvents(SDL_Event& e);

		bool touchesWall(Tile * tiles[]);

		//Make the character move in the map
		void move(Tile* tile[]);

		// sets the camera to the protagonist
		void setCamera(SDL_Rect& camera);

		// renders the protagonist to the screen.]// currently this is done in the renderer.cpp
		void render(SDL_Rect& camera);
	
		int getDirection()
		{
			return m_direction;
		}

		SDL_Rect getBox()
		{
			return m_box;
		}
	
	};
}

#endif