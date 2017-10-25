#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"

namespace apocalypsenow {

	const int ZOMBIE_MAX = 50;

	const int FRAME_TIME = 50;

	// zombie constants
	const int ZOMBIE_HEIGHT = 60;
	const int ZOMBIE_WIDTH = 60;
	const int ZOMBIE_FRAMES = 10;
	const int ZOMBIE_VELOCITY = 2;
	const int ZOMBIE_FRAME_DIRECTIONS = 4;

	// externals
	extern Tile* tiles[192];
	extern Bullet b[99];

	// Textures.
	extern Texture g_zombieLeft;
	extern Texture g_zombieRight;
	extern Texture g_zombieTop;
	extern Texture g_zombieBot;

	// Camera
	extern SDL_Rect g_camera;

	// Zombie clipper.
	extern SDL_Rect g_zombieClips[ZOMBIE_FRAME_DIRECTIONS][ZOMBIE_FRAMES];


	class Zombie:public GameObject
	{
	private:
		// if zero, then dead. 
		int m_health;
		int m_frame;
	public:
		Zombie();
		// Spawn location constructor.
		~Zombie();

		void update();
		void render();

		// Check for collision with bullet.
		bool collisionWithbullet(Bullet* bullet_);

		void spawn(int x_,int y_);
		void roam(Tile** tiles);

		bool isAlive() {
			return m_isAlive;
		}
	};

}