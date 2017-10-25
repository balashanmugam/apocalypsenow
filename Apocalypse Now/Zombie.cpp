#include "Zombie.h"
#include<stdlib.h>
#include <time.h>
#include <random>
#include "Tile.h"
namespace apocalypsenow{

	extern Player hero;
	// Creates a random direction
	int randomDistribution()
	{
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> random(0, 3);
		return random(rng);
	}

}
// Default constructor
apocalypsenow::Zombie::Zombie()
{
	// Oh the pun haha. This means zombie is dead dead, not dead alive.
	m_isAlive = false;
	m_health = 1;
	m_box.h = ZOMBIE_HEIGHT - 15;
	m_box.w = ZOMBIE_WIDTH - 25;
	m_direction = Direction::RIGHT;
	m_velX = 0;
	m_velY = 0;

	m_frame = 0;
}



apocalypsenow::Zombie::~Zombie()
{
}

void apocalypsenow::Zombie::update()
{
	roam(tiles);
	if (m_isAlive)
	{
		if (m_health == 0)
		{
			m_isAlive = false;
		}
	}
}

void apocalypsenow::Zombie::render()
{
	// rendering the zombies to the screen.
	
	if (m_isAlive)
	{
		SDL_Rect* currentFrame = &g_zombieClips[m_direction][m_frame];
		switch (m_direction)
		{
		case Direction::TOP:
			g_zombieTop.render(m_box.x - g_camera.x, m_box.y - g_camera.y, currentFrame);
			break;
		case Direction::BOTTOM:
			g_zombieBot.render(m_box.x - g_camera.x, m_box.y - g_camera.y, currentFrame);
			break;
		case Direction::LEFT:
			g_zombieLeft.render(m_box.x - g_camera.x, m_box.y - g_camera.y, currentFrame);
			break;
		case Direction::RIGHT:
			g_zombieRight.render(m_box.x - g_camera.x, m_box.y - g_camera.y, currentFrame);
			break;
		}

		if (m_frame >= ZOMBIE_FRAMES)
			m_frame = 0;
	}
}

bool apocalypsenow::Zombie::collisionWithbullet(Bullet* bullet_)
{
	bool flag = false;
	for (auto i = 0; i < BULLET_MAX; i++)
	{
		if (bullet_[i].isAlive() && collision(bullet_[i].getBox()))
		{
			bullet_[i].destroy();
			flag = true;
			break;
		}
	}
	return flag;
	
}

// set the starting point and make the dead alive.
// I will stop the pun.
void apocalypsenow::Zombie::spawn(int x_, int y_)
{
	m_isAlive = true;
	m_box.x = x_;
	m_box.y = y_;
	m_direction = static_cast<Direction>(randomDistribution());
}


// Just a patrol movement. If the zombie gets a whiff of the player, go in that direction maybe.
// move randomly in a direction if, an obstacle is there change direction and go.
// Seems simple enough. 
void apocalypsenow::Zombie::roam(Tile** tiles)
{
	srand(time(NULL));

	if (m_isAlive)
	{
		switch (m_direction)
		{
		case Direction::RIGHT:
			m_box.x += ZOMBIE_VELOCITY;
			
			for (auto i = 0; i < ZOMBIE_VELOCITY; i++)
			{
				if (i == 0)
					m_frame++;
				if (m_frame >= ZOMBIE_FRAMES)
					m_frame = 0;
			}

			// check for collision.
			if (m_box.x < 0 || m_box.x + ZOMBIE_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
			{
				// collision to unmoveable object occured.
				m_box.x -= ZOMBIE_VELOCITY;

				m_direction = static_cast<Direction>(randomDistribution());

				while (m_direction == Direction::RIGHT && m_direction == Direction::LEFT)
					m_direction = static_cast<Direction>(randomDistribution());
			}
			// Collision with hero.
			else if (collision(hero.getBox()))
			{
				// knock back
				hero.decreaseHealth();

				m_box.x -= 20 * ZOMBIE_VELOCITY;
			
			}
			else if (collisionWithbullet(b))
			{
				m_box.x -= 20 * ZOMBIE_VELOCITY;
				m_health--;
			}
			break;
		case Direction::LEFT:
			m_box.x -= ZOMBIE_VELOCITY;
			for (int i = 0; i <  ZOMBIE_VELOCITY; i++)
			{
				if (i == 0)
					m_frame++;

				if (m_frame >= ZOMBIE_FRAMES)
					m_frame = 0;
			}
			// check for collision.
			if (m_box.x < 0 || m_box.x + ZOMBIE_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
			{
				// collision to unmoveable object occured.
				m_box.x += ZOMBIE_VELOCITY;
				
				m_direction = static_cast<Direction>(randomDistribution());
				while (m_direction == Direction::LEFT && m_direction == Direction::RIGHT)
					m_direction = static_cast<Direction>(randomDistribution());
			}
			// Collision with hero.
			else if (collision(hero.getBox()))
			{
				// knock back
				m_box.x += 20 * ZOMBIE_VELOCITY;
				hero.decreaseHealth();
			}
			else if (collisionWithbullet(b))
			{
				m_box.x += 20 * ZOMBIE_VELOCITY;
				m_health--;
			}

			break;
		case Direction::BOTTOM:
			m_box.y += ZOMBIE_VELOCITY;
			for (int i = 0; i < ZOMBIE_VELOCITY; i++)
			{
				if (i == 0)
					m_frame++;

				if (m_frame >= ZOMBIE_FRAMES)
					m_frame = 0;
			}

			if (m_box.y < 0 || m_box.y + ZOMBIE_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
			{
				m_box.y -= ZOMBIE_VELOCITY;
				m_direction = static_cast<Direction>(randomDistribution());
				while (m_direction == Direction::BOTTOM && m_direction == Direction::TOP)
					m_direction = static_cast<Direction>(randomDistribution());

			}
			// Collision with hero.
			else if (collision(hero.getBox()))
			{
				// knock back
				hero.decreaseHealth();

				m_box.y -= 20 * ZOMBIE_VELOCITY;
			}
			else if (collisionWithbullet(b))
			{
				m_box.y -= 20 * ZOMBIE_VELOCITY;
				m_health--;
			}
			break;
		case Direction::TOP:
			m_box.y -= ZOMBIE_VELOCITY;
			for (int i = 0; i < ZOMBIE_VELOCITY; i++)
			{
				if (i == 0)
					m_frame++;

				if (m_frame >= ZOMBIE_FRAMES)
					m_frame = 0;
			}

			if (m_box.y < 0 || m_box.y + ZOMBIE_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
			{
				m_box.y += ZOMBIE_VELOCITY;

				m_direction = static_cast<Direction>(randomDistribution());
				while (m_direction == Direction::TOP && m_direction == Direction::BOTTOM)
					m_direction = static_cast<Direction>(randomDistribution());

			}
			// Collision with hero.
			else if (collision(hero.getBox()))
			{
				// knock back
				m_box.y += 20 * ZOMBIE_VELOCITY;
				hero.decreaseHealth();

			}
			else if (collisionWithbullet(b))
			{
				m_box.y += 20 * ZOMBIE_VELOCITY;
				SDL_Delay(50);
				m_health--;
			}
			break;

		}
	}
}


