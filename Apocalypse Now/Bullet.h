#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include "Renderer.h"
namespace apocalypsenow{

	class Texture;
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


	class Bullet
	{
	private:
		SDL_Rect m_box;
		bool m_isAlive;

		// Direction can be any of the four. Left, right, top , bottom.
		int m_direction;

	public:

		// Requires the origin point of the bullet and the direction along with which it passes.
		Bullet(int t_x,int t_y,int t_direction);
		Bullet();
		~Bullet();


		bool touchesWall(Tile * tiles[]);

		//Make the character move in the map
		void move(Tile* tile[]);

		// renders the protagonist to the screen.]// currently this is done in the renderer.cpp
		void render(SDL_Rect& camera);

		int getDirection()
		{
			return m_direction;
		}

		void destroy();


	};
}

#endif // !_BULLET_H_
