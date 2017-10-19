#include "Protagonist.h"

namespace apocalypsenow{
	extern SDL_Rect g_camera;
	extern Protagonist hero;
}
apocalypsenow::Protagonist::Protagonist(int t_x, int t_y)
{
	m_box.x = t_x;
	m_box.y = t_y;
	m_box.h = PROT_HEIGHT;// -15;
	m_box.w = PROT_WIDTH;// -15;

	m_frame = 0;

	m_direction = Direction::RIGHT;
}
void apocalypsenow::Protagonist::render(SDL_Rect& camera)
{
	SDL_Rect* currentFrame = &g_protagonistClips[m_direction][m_frame];
	//apocalypsenow::errorfile << "Frame no: " << m_frame << std::endl;

	switch (m_direction)
	{
	case Direction::TOP:
		g_protagonistTextureTop.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
		break;
	case Direction::BOTTOM:
		g_protagonistTextureBot.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
		break;
	case Direction::LEFT:
		g_protagonistTextureLeft.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
		break;
	case Direction::RIGHT:
		g_protagonistTextureRight.render(m_box.x - camera.x, m_box.y - camera.y, currentFrame);
		break;
	}

	if (m_frame >= PROT_TOTAL_FRAMES)
		m_frame = 0;

	
	SDL_RenderPresent(g_renderer);

}

void apocalypsenow::Protagonist::update()
{
}

void apocalypsenow::Protagonist::handleEvents(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		
		// increase velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			m_velY -= PROT_SPEED;
			m_direction = Direction::TOP;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			m_velY += PROT_SPEED;
			m_direction = Direction::BOTTOM;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			m_velX -= PROT_SPEED;
			m_direction = Direction::LEFT;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			m_velX += PROT_SPEED;
			m_direction = Direction::RIGHT;
			break;
		
		case SDLK_SPACE: 
			//
			
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			m_velY += PROT_SPEED;
			m_direction = Direction::TOP;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			m_velY -= PROT_SPEED;
			m_direction = Direction::BOTTOM;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			m_velX += PROT_SPEED;
			m_direction = Direction::LEFT;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			m_velX -= PROT_SPEED;
			m_direction = Direction::RIGHT;
			break;

		case SDLK_SPACE:
			break;
		}
	}
}

void apocalypsenow::Protagonist::move(Tile* tiles[])
{

	// if the character moves left/ right

	m_box.x += m_velX;
	for (int i = 0; i < m_velX ;i++)
	{
		if (i % 12 == 0)
			m_frame++;
		
		if (m_frame >= PROT_TOTAL_FRAMES)
			m_frame = 0;

	}

	for (int i = 0; i < (-1 * m_velX); i++)
	{
		if (i % 12 == 0)
			m_frame++;

		if (m_frame >= PROT_TOTAL_FRAMES)
			m_frame = 0;
	}

	// if the character went out of the screen to the left, or the right, or in case it runs into a wall
	if (m_box.x < 0 || m_box.x + PROT_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
	{
		m_box.x -= m_velX;
	}

	// if the character moves up and down

	m_box.y += m_velY;
	for (int i = 0; i < m_velY; i++)
	{
		if (i % 12 == 0)
			m_frame++;

		if (m_frame >= PROT_TOTAL_FRAMES)
			m_frame = 0;

	}
	for (int i = 0; i < (-1 * m_velY); i++)
	{
		if (i % 12 == 0)
			m_frame++;

		if (m_frame >= PROT_TOTAL_FRAMES)
			m_frame = 0;
	}

	// if the character went too far to the top , or bottom, or touches the wall
	if (m_box.y < 0 || m_box.y + PROT_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
	{
		m_box.y -= m_velY;
	}

	//errorfile << "Location: " << this->m_box.x << "  "<< this->m_box.y << std::endl;

}

void apocalypsenow::Protagonist::setCamera(SDL_Rect& camera)
{
	// Centers the camer over the character.
	camera.x = (m_box.x + PROT_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (m_box.y + PROT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

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

