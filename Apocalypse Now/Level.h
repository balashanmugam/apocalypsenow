#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Tile.h"
namespace apocalypsenow {
	

	// externs
	//extern std::ifstream errorfile;
	extern Tile* tiles[TILE_TOTAL];
	extern SDL_Rect g_camera;

	typedef struct Point {
		int x;
		int y;
	}Point;
	
	const int MAX_LEVELS = 2;
	const int ZOMBIE_SPAWNS = 3;
	const int KEY_COUNT = 3;
	
	class Level
	{
	private:
		Point m_playerSpawn;
		Point m_zombieSpawn[ZOMBIE_SPAWNS];
		std::ifstream m_mapFile;
		std::string m_fileName;
		Point m_keySpawn[KEY_COUNT];
		void closeLevel();
	public:
		Level();
		~Level();

		void loadLevel();
		void loadNextLevel();

		Point getPlayerSpawn();

		void render();
		void setFileName(std::string filename_);
		void close();
	};
}