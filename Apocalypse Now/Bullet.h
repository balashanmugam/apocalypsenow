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
	const int BULLET_WIDTH = 25;
	const int BULLET_HEIGHT = 25;
	
	// bullet velocity.
	const int BULLET_VELOCITY = 7;

	extern Texture g_bulletTextureLeft;
	extern Texture g_bulletTextureBot;
	extern Texture g_bulletTextureRight;
	extern Texture g_bulletTextureTop;
	extern SDL_Rect g_bulletClip;
	extern SDL_Rect g_camera;

	class Bullet:public GameObject
	{

	public:

		Bullet();

		// Gets the starting location of the bullet.  
		Bullet(int x, int y);
		
		~Bullet();

		//Make the character move in the map
		void fireBullet(int x_, int y_, apocalypsenow::Direction dir_);

		// renders the protagonist to the screen.// currently this is done in the renderer.cpp
		void render();

		void destroy();

		// updates the location of the charracter
		void update();


	};
}

#endif // !_BULLET_H_
