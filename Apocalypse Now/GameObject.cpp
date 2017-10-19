#include "GameObject.h"

apocalypsenow::GameObject::GameObject()
{
	
}

apocalypsenow::GameObject::GameObject(SDL_Rect box, Direction d, int velX,int velY)
{
	m_box = box;
	m_direction = d;
	m_velX = velX;
	m_velY = velY;
	m_isAlive = true; // For players it is health. For bullets it's presence, For zombies it is their life.// Oh wait. Zombies don't have health.

}

apocalypsenow::GameObject::~GameObject()
{
}


bool apocalypsenow::GameObject::collision(SDL_Rect box)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int botA, botB;

	// Calculate A values.
	leftA = this->m_box.x;
	rightA = this->m_box.x + this->m_box.w;
	topA = this->m_box.y;
	botA = this->m_box.y + this->m_box.h;

	// Similarly, calculate B
	leftB = box.x;
	rightB = box.x + box.w;
	topB = box.y;
	botB = box.y + box.h;


	if (botA <= topB)
	{
		return false;
	}
	if (topA >= botB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}
	return true;
}
bool apocalypsenow::GameObject::collision(GameObject * t_object)
{
	return collision(t_object->m_box);
}

bool apocalypsenow::GameObject::touchesWall(Tile* tiles[])
{
	// go though each tile
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		if ((tiles[i]->getType() >= TILE_MID) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			if (collision(tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	return false;
}
