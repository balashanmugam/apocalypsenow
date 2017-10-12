#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "Renderer.h"

namespace apocalypsenow
{ 
	class Tiles;
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
		int m_velocity;
		bool m_isAlive;
	public:

		GameObject(SDL_Rect box, direction d, int velocity);
		~GameObject();
		bool collision(GameObject* t_object);
		bool touchesWall(Tiles* tiles);
		
	};
}

#endif
