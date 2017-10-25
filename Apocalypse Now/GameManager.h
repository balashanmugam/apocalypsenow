#pragma once
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Texture.h"
#include "Tile.h"
#include "Timer.h"

// This class will load all the necessary things required for the game.
// Also, this class will contain the GAME LOOP
namespace apocalypsenow {

	enum GameState {
		MENU,
		PLAYING,
		WIN,
		DEAD,
		GAMEOVER
	};
	extern SDL_Renderer* g_renderer;
	extern std::fstream errorfile;
	extern std::ifstream test;

	//SDL_Renderer* g_bulletRenderer;

	// Screens constants
	const int SCREEN_WIDTH = 400;
	const int SCREEN_HEIGHT = 320;

	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	// Level Constants

	class Bullet;

	class GameManager
	{
	private:
		// Screen dimensions

		SDL_Event m_event;
	
		SDL_Window* m_window;
		GameState m_state;
				
		// if this flag is set to true, the game has ended.
		bool m_exit;

		// current level.
		unsigned int m_level;

		//Player hero;
	
	public:

		// Initializes member variables.
		GameManager();

		// Deallocates memory in the member variable (Pointers)
		~GameManager();
	
		// Initializes all the necessary modules.
		bool init();

		void update();

		// init Main menu
		void loadMainMenu();
		// Set the game state based on event handlers.
		void setState(GameState state_);


		// test function.

		void loadLevel();

		void test_displaylevel();
		// Refreshed the sprites of the level.
		void refreshLevel();

		void render();

		//handles all the input events
		void handleEvents();

		//returns m_exit
		bool getExit() const;

		//Execute init, update and render.
		void execute();

		void cleanup();
	
	};

}
#endif // !_RENDERER_H_
