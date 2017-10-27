#include "Level.h"

void apocalypsenow::Level::closeLevel()
{
	m_mapFile.close();
}

apocalypsenow::Level::Level()
{
}

apocalypsenow::Level::~Level()
{
}

void apocalypsenow::Level::setZombieSpawns(Point * p_)
{
	for (auto i = 0; i < ZOMBIE_SPAWNS; i++)
	{
		m_zombieSpawn[i].x = p_[i].x;
		m_zombieSpawn[i].y = p_[i].y;
	}
}

void apocalypsenow::Level::setKeySpawns(Point * p_)
{
	for (auto i = 0; i < KEY_COUNT; i++)
	{
		m_keySpawn[i].x = p_[i].x;
		m_keySpawn[i].y = p_[i].y;
	}
}

void apocalypsenow::Level::setPlayerSpawn(int x_, int y_)
{
	m_playerSpawn.x = x_;
	m_playerSpawn.y = y_;
}


void apocalypsenow::Level::loadLevel()
{
	std::ifstream m_map(m_fileName);

	int x = 0;
	int y = 0;

	if (m_map.fail() == true)
	{
		errorfile << "File Loading failed: Unable to load file." << std::endl;
	}
	// load map.
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		int tileType = -1;

		m_map >> tileType;

		if (m_map.fail())
		{
			errorfile << "File reading error: Unexpected end of file." << std::endl;
			break;
		}

		// Check if it is a valid tile.
		if ((tileType >= 0 && tileType < TILE_TYPES) || tileType == TILE_BLOCK || tileType == TILE_EXIT)
		{
			tiles[i] = new Tile(x, y, tileType);

		}

		// Next horizontal tile location		
		x += TILE_WIDTH;

		// if the tile reaches the end of the level width.
		if (x >= LEVEL_WIDTH)
		{
			x = 0;
			y += TILE_HEIGHT;
		}

	}
}

apocalypsenow::Point apocalypsenow::Level::getPlayerSpawn()
{
	return m_playerSpawn;
}

apocalypsenow::Point* apocalypsenow::Level::getKeySpawn()
{
	return m_keySpawn;
}

apocalypsenow::Point * apocalypsenow::Level::getZombieSpawns()
{
	return m_zombieSpawn;
}

void apocalypsenow::Level::render()
{

	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		tiles[i]->render(g_camera);
	}
}

void apocalypsenow::Level::setFileName(std::string filename_)
{
	m_fileName = filename_;
}

void apocalypsenow::Level::close()
{
	m_mapFile.close();
}
