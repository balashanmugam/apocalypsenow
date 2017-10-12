#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "Renderer.h"

namespace apocalypsenow
{ 
	class Tile;
	enum direction
	{
		LEFT,
		BOTTOM,
		RIGHT,
		TOP
	};
	class GameObject
	{
	protected:
		SDL_Rect m_box;
		direction m_direction;
		int m_velX;
		int m_velY;
		bool m_isAlive;
	public:

		GameObject(SDL_Rect box, direction d, int velX,int velY);
		~GameObject();
		bool collision(GameObject* t_object);
		bool collision(SDL_Rect box);
		bool touchesWall(Tile* tiles[]);
		
	};
}

#endif
