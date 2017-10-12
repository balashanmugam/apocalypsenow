#include "GameObject.h"

apocalypsenow::GameObject::GameObject(SDL_Rect box, direction d, int velocity)
{
	m_box = box;
	m_direction = d;
	m_velocity = velocity;
	m_isAlive = true; // For players it is health. For bullets it's presence, For zombies it is their life.// Oh wait. Zombies don't have health.

}

bool apocalypsenow::GameObject::collision(GameObject * t_object)
{
	// go though each tile
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		if (tiles[i]->getType() == TILE_BLOCK)
		{
			if (checkCollision(tiles[i]->getBox(), this->m_box))
			{
				apocalypsenow::errorfile << "Collision : " << tiles[i]->getType() << "  " << this->m_box.x << "  " << this->m_box.y << std::endl;
				return true;
			}
		}
	}
	return false;
}
