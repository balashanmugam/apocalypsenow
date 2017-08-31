#pragma once
#ifndef _PROTAGONIST_H_
#define _PROTAGONIST_H_

#include "Renderer.h"

namespace apocalypsenow {

	//extern Tile* tiles[TILE_TYPES];4

	class Texture;
	class Tile;

	extern Texture g_protagonistTexture;
	extern SDL_Rect g_protagonistClips[];
	//bool touchesWall(SDL_Rect box, Tile* tiles[]);

	const int PROT_WALK_LEFT = 0;
	const int PROT_WALK_BOT = 1;
	const int PROT_WALK_RIGHT = 2;
	const int PROT_WALK_TOP = 3;

	const int PROT_TOTAL_FRAMES = 10;

	const int PROT_WIDTH = 60;
	const int PROT_HEIGHT = 60;


	
	// PROT aka Protagonist.
	class Protagonist
	{
	private:
		std::string m_name;

		int m_velX; // velocity in x direction
		int m_velY; // Velocity in y directed.

		// current frame
		int m_frame;

		SDL_Rect m_box;


	public:
		static const int PROT_WIDTH = 60;
		static const int PROT_HEIGHT = 60;

		static const int PROT_SPEED = 2;

		Protagonist();

		//Handle events 
		void handleEvents(SDL_Event& e);

		bool touchesWall(Tile * tiles[]);

		//Make the character move in the map
		void move(Tile* tile[]);

		// sets the camera to the protagonist
		void setCamera(SDL_Rect& camera);


		// renders the protagonist to the screen.]// currently this is done in the renderer.cpp
		 // TODO : Please change it to render here later. if possible.
		void render(SDL_Rect& camera);
	};
}

#endif