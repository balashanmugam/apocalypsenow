#include "Bullet.h"


apocalypsenow::Bullet::Bullet()
{
	m_box.x = 0;
	m_box.y = 0;
	m_box.h = BULLET_HEIGHT;
	m_box.w = BULLET_WIDTH;
	m_isAlive = true;

	m_direction = Direction::RIGHT;
}
void apocalypsenow::Bullet::render()
{

	g_bulletTexture.render(m_box.x,m_box.y ,&g_bulletClip);
	SDL_RenderPresent(g_renderer);

}

void apocalypsenow::Bullet::update()
{

}

void apocalypsenow::Bullet::launch(Tile* tiles[])
{

		apocalypsenow::errorfile << "Bullet Spawn Point: " << m_box.x << "  " << m_box.y << std::endl;
		while(this->m_isAlive)
		{
		
			m_box.x += BULLET_VELOCITY;

			// Bullets horizontal movement
			// if the character went out of the screen to the left, or the right, or in case it runs into a wall
			if (m_box.x < 0 || m_box.x + PROT_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
			{
				m_box.x -= BULLET_VELOCITY;
				// destroy
				m_isAlive = false;

			}

			// if the character moves up and down
			render();
		}
		//g_quitThread = true;
}
apocalypsenow::Bullet::~Bullet()
{
	// 
}


