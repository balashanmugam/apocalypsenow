#include "Key.h"

apocalypsenow::Key::Key()
{
	m_box.h = KEY_HEIGHT;
	m_box.w = KEY_WIDTH;
	m_isAlive = false;
}

apocalypsenow::Key::~Key()
{
}

void apocalypsenow::Key::render()
{
	if(m_isAlive)
		g_keyTexture.render(m_box.x - g_camera.x, m_box.y - g_camera.y);
}

void apocalypsenow::Key::spawnAt(int x_, int y_)
{
	m_box.x = x_;
	m_box.y = y_;

	m_isAlive = true;
}

void apocalypsenow::Key::update()
{
	if(m_isAlive)
	{
		if (collision(hero.getBox()))
		{
			hero.incrementKeyCount();
			m_isAlive = false;
		}
	}	
}


