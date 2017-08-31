#include "Protagonist.h"

apocalypsenow::Protagonist::Protagonist()
{
	// init all
	m_name = "Dummy";
	m_velX = 0;
	m_velY = 0;

	m_box.x = 0;
	m_box.y = 0;
	m_box.h = 0;
	m_box.w = 0;

	m_frame = 0;

}
void apocalypsenow::Protagonist::render(SDL_Rect& camera)
{
	SDL_Rect* currentFrame = &g_protagonistClips[m_frame / 10];
	g_protagonistTexture.render(m_box.x - camera.x,m_box.y - camera.y , currentFrame);
	m_frame++;
	if (m_frame / 10 >= PROT_TOTAL_FRAMES)
		m_frame = 0;

	SDL_RenderPresent(g_renderer);

}

void apocalypsenow::Protagonist::handleEvents(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// increase velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			m_velY -= PROT_SPEED;
			break;
		case SDLK_s:
			m_velY += PROT_SPEED;
			break;
		case SDLK_a:
			m_velX -= PROT_SPEED;
			break;
		case SDLK_d:
			m_velX += PROT_SPEED;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				m_velY += PROT_SPEED;
				break;
			case SDLK_s:
				m_velY -= PROT_SPEED;
				break;
			case SDLK_a:
				m_velX += PROT_SPEED;
				break;
			case SDLK_d:
				m_velX -= PROT_SPEED;
				break;

			}
	}
}

bool apocalypsenow::Protagonist::touchesWall(Tile* tiles[])
{
	// go though each tile
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		if ((tiles[i]->getType() >= TILE_MID) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			if (checkCollision(m_box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	return false;
}

void apocalypsenow::Protagonist::move(Tile* tiles[])
{

	// if the character moves left/ right

	m_box.x += m_velX;

	// if the character went out of the screen to the left, or the right, or in case it runs into a wall
	if (m_box.x < 0 || m_box.x + PROT_WIDTH > LEVEL_WIDTH || touchesWall(tiles))
	{
		m_box.x -= m_velX;
	}

	// if the character moves up and down

	m_box.y += m_velY;

	// if the character went too far to the top , or bottom, or touches the wall
	if (m_box.y < 0 || m_box.y + PROT_HEIGHT > LEVEL_HEIGHT || touchesWall(tiles))
	{
		m_box.y -= m_velY;
	}
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
