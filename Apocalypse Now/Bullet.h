#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Texture.h"
#include "Tile.h"
#include "Timer.h"
#include "Protagonist.h"


namespace apocalypsenow{
	class Texture;
	class Tile;

	// bullet dimensions
	const int BULLET_WIDTH = 10;
	const int BULLET_HEIGHT = 10;
	
	// bullet velocity.
	const int BULLET_VELOCITY = 5;

	extern Texture g_bulletTexture;
	extern SDL_Rect g_bulletClip;

	class Bullet:public GameObject
	{

	public:

		Bullet();

		~Bullet();

		//Make the character move in the map
		void launch(Tile* tile[]);

		// renders the protagonist to the screen.// currently this is done in the renderer.cpp
		void render();

		void destroy();

		// updates the location of the charracter
		void update();


	};
}

#endif // !_BULLET_H_
