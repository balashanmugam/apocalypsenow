#include "Tile.h"


namespace apocalypsenow
{
	extern Texture g_tileTexture;
	extern SDL_Rect g_tileClip[TILE_TYPES];
	extern SDL_Rect g_blockTileClip;
	extern Texture g_blockTileTexture;
	extern Texture g_exitTexture;
}
apocalypsenow::Tile::Tile(int t_x, int t_y, int t_tileType)
{
	m_box.x = t_x;
	m_box.y = t_y;

	m_box.w = TILE_WIDTH;
	m_box.h = TILE_HEIGHT;

	m_type = t_tileType;

}

void apocalypsenow::Tile::render(SDL_Rect& t_camera)
{
	if (checkCollision(t_camera, m_box) == true)
	{
		g_tileTexture.render(m_box.x - t_camera.x, m_box.y - t_camera.y, &g_tileClip[m_type]);

		if(m_type == TILE_BLOCK)
			g_blockTileTexture.render(m_box.x - t_camera.x, m_box.y - t_camera.y, &g_blockTileClip);
		else if (m_type == TILE_EXIT)
			g_exitTexture.render(m_box.x - t_camera.x, m_box.y - t_camera.y);
	}
}

int apocalypsenow::Tile::getType()
{
	return m_type;
}

SDL_Rect apocalypsenow::Tile::getBox()
{
	return m_box;
}

bool apocalypsenow::checkCollision(SDL_Rect t_a, SDL_Rect t_b)
{

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int botA, botB;

	// Calculate A values.
	leftA = t_a.x;
	rightA = t_a.x + t_a.w;
	topA = t_a.y;
	botA = t_a.y + t_a.h;

	// Similarly, calculate B
	leftB = t_b.x;
	rightB = t_b.x + t_b.w;
	topB = t_b.y;
	botB = t_b.y + t_b.h;


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