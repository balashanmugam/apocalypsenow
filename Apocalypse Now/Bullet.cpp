#include "Bullet.h"

apocalypsenow::Bullet::Bullet(int t_x, int t_y, int t_direction)
{
	m_box.x = t_x;
	m_box.y = t_y;

	m_box.h = BULLET_HEIGHT;
	m_box.w = BULLET_WIDTH;

	m_direction = t_direction;
}
