#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_thread.h"

#include "Bullet.h"
#include "Texture.h"
#include "Tile.h"
#include "Timer.h"
#include "Protagonist.h"

// This class will load all the necessary things required for the game.
// Also, this class will contain the GAME LOOP
namespace apocalypsenow {


	extern SDL_Renderer* g_renderer;
	extern std::fstream errorfile;
	extern std::ifstream test;

	//SDL_Renderer* g_bulletRenderer;

	// Screens constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	// Level Constants
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;
	class Bullet;

	class Renderer
	{
	private:
		// Screen dimensions

		SDL_Event m_event;
	
		SDL_Window* m_window;
				
		// if this flag is set to true, the game has ended.
		bool m_exit;

		//Protagonist hero;
	
	public:

		// Initializes member variables.
		Renderer();

		// Deallocates memory in the member variable (Pointers)
		~Renderer();
	
		// Initializes all the necessary modules.
		bool init();

		void update();




		// test function.

		void test_loadLevel();

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
