#include "Player.h"


namespace apocalypsenow{
	extern SDL_Rect g_camera;
	extern Zombie z[ZOMBIE_MAX];
}
apocalypsenow::Player::Player()
{
	m_box.h = PLAYER_HEIGHT - 15;
	m_box.w = PLAYER_WIDTH - 15;

	m_frame = 0;
	m_health = 50;

	m_isAlive = true;

	m_direction = Direction::RIGHT;

	m_keys = 0;
	m_win = false;
}
apocalypsenow::Player::Player(int t_x, int t_y)
{

	m_keys = 0;
	m_win = false;
	
	m_box.x = t_x;
	m_box.y = t_y;
	m_box.h = PLAYER_HEIGHT -15;
	m_box.w = PLAYER_WIDTH -15;

	m_frame = 0;
	m_health = 50;

	m_isAlive = true;

	m_direction = Direction::RIGHT;
}
void apocalypsenow::Player::render(SDL_Rect& camera)
{
	SDL_Rect* currentFrame = &g_playerClips[m_direction][m_frame];
	//apocalypsenow::errorfile << "Frame no: " << m_frame << std::endl;
	SDL_Color r;
	r.r = 255;
	r.g = 200;
	r.b = 200;
	if (m_isAlive)
	{

		switch (m_direction)
		{
		case Direction::TOP:
			g_playerTextureTop.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
			//g_playerTextureTop.setColor(r);
			break;
		case Direction::BOTTOM:
			g_playerTextureBot.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
			break;
		case Direction::LEFT:
			g_playerTextureLeft.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
			break;
		case Direction::RIGHT:
			g_playerTextureRight.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
			break;
		}
	if (m_frame >= PLAYER_TOTAL_FRAMES)
		m_frame = 0;
	}

}

void apocalypsenow::Player::setSpawn(apocalypsenow::Point p_)
{
	m_box.x = p_.x;
	m_box.y = p_.y;
}

void apocalypsenow::Player::update()
{

	move(tiles);
	if(m_health <= 0 )
		m_isAlive = false;

	
}

void apocalypsenow::Player::handleEvents(SDL_Event& e)
{

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		
		// increase velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			m_velY -= PLAYER_VELOCITY;
			m_direction = Direction::TOP;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			m_velY += PLAYER_VELOCITY;
			m_direction = Direction::BOTTOM;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			m_velX -= PLAYER_VELOCITY;
			m_direction = Direction::LEFT;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			m_velX += PLAYER_VELOCITY;
			m_direction = Direction::RIGHT;
			break;
		
		case SDLK_SPACE: 
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			m_velY += PLAYER_VELOCITY;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			m_velY -= PLAYER_VELOCITY;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			m_velX += PLAYER_VELOCITY;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			m_velX -= PLAYER_VELOCITY;
			break;

		case SDLK_SPACE:
			break;
		}
	}

}

void apocalypsenow::Player::move(Tile* tiles[])
{

	// if the character moves left/ right

	m_box.x += m_velX;

	
	for (int i = 0; i < m_velX; i++)
	{
		if (i == 0)
			m_frame++;
		if (m_frame >= PLAYER_TOTAL_FRAMES)
			m_frame = 0;
	}
	for (int i = 0; i < (-1 * m_velX); i++)
	{
		if (i == 0)
			m_frame++;

		if (m_frame >= PLAYER_TOTAL_FRAMES)
			m_frame = 0;
	}
	// if the character went out of the screen to the left, or the right, or in case it runs into a wall
	if (m_box.x < 0 || m_box.x + PLAYER_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
	{
		m_box.x -= m_velX;
	}
	// if the character reaches the exit.
	else if (touchesTrapdoor(tiles))
	{
		// and he even has all the keys to make it through
		if (m_keys == KEY_COUNT)
		{
			// Game win condition.
			m_win = true;
			
		}
	}


	// if the character moves up and down

	m_box.y += m_velY;

	for (int i = 0; i < m_velY; i++)
	{
		if (i == 0)
			m_frame++;
		if (m_frame >= PLAYER_TOTAL_FRAMES)
			m_frame = 0;
	}
	for (int i = 0; i < (-1 * m_velY); i++)
	{
		if (i == 0)
			m_frame++;

		if (m_frame >= PLAYER_TOTAL_FRAMES)
			m_frame = 0;
	}

	// if the character went too far to the top , or bottom, or touches the wall
	if (m_box.y < 0 || m_box.y + PLAYER_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
	{
		m_box.y -= m_velY;
	}
	// if the character reaches the exit.
	else if (touchesTrapdoor(tiles))
	{
		// and he even has all the keys to make it through
		if (m_keys == KEY_COUNT)
		{
			// Game win condition.
			m_win = true;

		}
	}

}

bool apocalypsenow::Player::collisionWithZombies(Zombie * z_)
{
	bool flag = false;
	for (auto i = 0; i < ZOMBIE_MAX; i++)
	{
		if (z_[i].isAlive() && collision(z_[i].getBox()))
		{

			flag = true;
			break;
		}
	}
	return flag;

}

void apocalypsenow::Player::setCamera(SDL_Rect& camera)
{
	// Centers the camer over the character.
	camera.x = (m_box.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (m_box.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	// Keeping the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

bool apocalypsenow::Player::touchesTrapdoor(Tile ** tiles)
{
	// go though each tile
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		if (tiles[i]->getType() == TILE_EXIT)
		{
			if (collision(tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	return false;
}
