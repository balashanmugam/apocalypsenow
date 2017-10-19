#pragma once
#ifndef _PROTAGONIST_H_
#define _PROTAGONIST_H_

#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Texture.h"
#include "Tile.h"
#include "Timer.h"


namespace apocalypsenow {

	//extern Tile* tiles[TILE_TYPES];4

	class Texture;
	class Tile;


	//bool touchesWall(SDL_Rect box, Tile* tiles[]);

	const int PROT_WALKING_DIRECTION = 4;
	const int PROT_TOTAL_FRAMES = 10;

	const int PROT_WIDTH = 60;
	const int PROT_HEIGHT = 60;

	const int PROT_SPEED = 3;

	extern Texture g_protagonistTextureTop;
	extern Texture g_protagonistTextureBot;
	extern Texture g_protagonistTextureLeft;
	extern Texture g_protagonistTextureRight;
	extern SDL_Rect g_protagonistClips[PROT_WALKING_DIRECTION][PROT_TOTAL_FRAMES];

	extern Tile* tiles[192];

	// PROT aka Protagonist.
	class Protagonist: public GameObject
	{
	private:
		std::string m_name;

		int m_frame;

	public:
		//Protagonist();

		Protagonist(int t_x, int tx_y);
		
		//Handle events 
		void handleEvents(SDL_Event& e);

		//Make the character move in the map
		void move(Tile* tile[]);

		// sets the camera to the protagonist
		void setCamera(SDL_Rect& camera);

		// renders the protagonist to the screen.]// currently this is done in the renderer.cpp
		void render(SDL_Rect& camera);

		// updates the location of the charracter
		void update();
	
	
	};
}

#endif