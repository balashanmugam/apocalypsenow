#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <SDL.h>
#include "Tile.h"

namespace apocalypsenow
{ 
	class Tile;
	enum Direction
	{
		LEFT,
		BOTTOM,
		RIGHT,
		TOP 
	};

	// Base class for all objects to be spawned inside the map/screen.
	class GameObject
	{
	protected:
		SDL_Rect m_box;
		Direction m_direction;
		int m_velX;
		int m_velY;
		bool m_isAlive;
	public:

		GameObject();
		GameObject(SDL_Rect box, Direction d, int velX,int velY);
		~GameObject();
		bool collision(GameObject* t_object);
		bool collision(SDL_Rect box);
		bool touchesWall(Tile* tiles[]);

		virtual void update() = 0;
		Direction getDirection()
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
