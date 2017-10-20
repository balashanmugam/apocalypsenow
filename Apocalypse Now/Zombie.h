#pragma once
#include "GameObject.h"

namespace apocalypsenow {


	const int FRAME_TIME = 50;

	// zombie constants
	const int ZOMBIE_HEIGHT = 60;
	const int ZOMBIE_WIDTH = 60;
	const int ZOMBIE_FRAMES = 6;
	const int ZOMBIE_VELOCITY = 3;
	extern Tile* tiles[192];

	// Textures.
	extern Texture g_zombieLeft;
	extern Texture g_zombieRight;
	extern Texture g_zombieTop;
	extern Texture g_zombieBot;

	// Camera
	extern SDL_Rect g_camera;

	// Zombie clipper.
	extern SDL_Rect g_zombieClips[4][ZOMBIE_FRAMES];


	class Zombie:public GameObject
	{
	private:
		int m_hitsTaken;
		int m_frame;
	public:
		Zombie();
		// Spawn location constructor.
		~Zombie();

		void update();
		void render();

		void spawn(int x_,int y_);
		void roam(Tile** tiles);
	};

}