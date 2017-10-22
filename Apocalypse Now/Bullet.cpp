#include "Bullet.h"


apocalypsenow::Bullet::Bullet()
{
	m_box.h = BULLET_HEIGHT;
	m_box.w = BULLET_WIDTH;
	m_isAlive = false;

	m_direction = Direction::RIGHT;
}


void apocalypsenow::Bullet::render()
{
	if (m_isAlive)
	{
		switch (m_direction)
		{
		case Direction::LEFT:
			g_bulletTextureLeft.render(m_box.x  - g_camera.x, m_box.y - g_camera.y, &g_bulletClip);
			break;
		case Direction::RIGHT:
			g_bulletTextureRight.render(m_box.x - g_camera.x, m_box.y - g_camera.y, &g_bulletClip);
			break;
		case Direction::TOP:
			g_bulletTextureTop.render(m_box.x   - g_camera.x, m_box.y - g_camera.y, &g_bulletClip);
			break;
		case Direction::BOTTOM:
			g_bulletTextureBot.render(m_box.x   - g_camera.x, m_box.y - g_camera.y, &g_bulletClip);
			break;
		}
	}
}

void apocalypsenow::Bullet::destroy()
{
	if (m_isAlive)
		m_isAlive = false;
}

void apocalypsenow::Bullet::update()
{
	if (m_isAlive)
	{
		if (m_direction == Direction::RIGHT)
		{
			m_box.x += BULLET_VELOCITY;
			if (m_box.x < 0 || m_box.x + BULLET_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
			{
				m_box.x -= BULLET_VELOCITY;
				m_isAlive = false;
			}
		}
		else if (m_direction == Direction::LEFT)
		{
			m_box.x -= BULLET_VELOCITY;
			if (m_box.x < 0 || m_box.x + BULLET_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
			{
				m_box.x += BULLET_VELOCITY;
				m_isAlive = false;
			}
		}
		else if (m_direction == Direction::BOTTOM)
		{
			m_box.y += BULLET_VELOCITY;
			if(m_box.y < 0 || m_box.y + BULLET_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
			{
				m_box.y -= BULLET_VELOCITY;
				m_isAlive = false;
			}
		}
		else if (m_direction == Direction::TOP)
		{
			m_box.y -= BULLET_VELOCITY;
			if (m_box.y < 0 || m_box.y + BULLET_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
			{
				m_box.y += BULLET_VELOCITY;
				m_isAlive = false;
			}
		}
	}
}

void apocalypsenow::Bullet::fireBullet(int x_, int y_,apocalypsenow::Direction dir_ )
{
	m_box.x = x_;
	m_box.y = y_;
	m_direction = dir_;
	m_isAlive = true;

}
apocalypsenow::Bullet::~Bullet()
{
	// 
}


