#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include "Renderer.h"

namespace apocalypsenow{

	class Texture;
	class GameObject;
	class Tile;

	// bullet dimensions
	const int BULLET_WIDTH = 10;
	const int BULLET_HEIGHT = 10;
	
	// bullet velocity.
	const int BULLET_VELOCITY = 5;

	//Bullet directions .
	const int BULLET_LEFT = 0;
	const int BULLET_BOT = 1;
	const int BULLET_RIGHT = 2;
	const int BULLET_TOP = 3;

	extern Texture g_bulletTexture;
	extern SDL_Rect g_bulletClip;

	class Bullet:public GameObject
	{

	public:

		// Requires the origin point of the bullet and the direction along with which it passes.
		Bullet();

		~Bullet();

		//Make the character move in the map
		void launch(Tile* tile[]);

		// renders the protagonist to the screen.// currently this is done in the renderer.cpp
		void render();

		int getDirection()
		{
			return m_direction;
		}

		void destroy();


	};
}

#endif // !_BULLET_H_
