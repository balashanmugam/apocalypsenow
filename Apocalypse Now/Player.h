#pragma once
#ifndef _PROTAGONIST_H_
#define _PROTAGONIST_H_

#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Zombie.h"
#include "Texture.h"
#include "Tile.h"
#include "Timer.h"
#include "Level.h"


namespace apocalypsenow {

	class Texture;
	class Tile;
	class Zombie;

	const int DIRECTION_TOTAL = 4;
	const int PLAYER_TOTAL_FRAMES = 10;

	const int PLAYER_WIDTH = 60;
	const int PLAYER_HEIGHT = 60;

	const int PLAYER_VELOCITY = 2;



	extern Texture g_playerTextureTop;
	extern Texture g_playerTextureBot;
	extern Texture g_playerTextureLeft;
	extern Texture g_playerTextureRight;
	extern SDL_Rect g_playerClips[DIRECTION_TOTAL][PLAYER_TOTAL_FRAMES];

	extern Tile* tiles[192];

	// PROT aka Player.
	class Player: public GameObject
	{
	private:
		std::string m_name;

		int m_frame;
		int m_health;

	public:
		Player();

		Player(int t_x, int tx_y);
		
		//Handle events 
		void handleEvents(SDL_Event& e);

		//Make the character move in the map
		void move(Tile* tile[]);

		//Check if a collision with zombies occur
		bool collisionWithZombies(Zombie* z_);


		// sets the camera to the protagonist
		void setCamera(SDL_Rect& camera);

		// renders the protagonist to the screen.]// currently this is done in the renderer.cpp
		void render(SDL_Rect& camera);

		void setSpawn(apocalypsenow::Point p_);

		// On hit from a zombie, reduces the health.
		void decreaseHealth() {
			m_health--;
		}

		// updates the location of the charracter
		void update();

		bool isAlive() {
			return m_isAlive;
		}
	
	
	};
}

#endif