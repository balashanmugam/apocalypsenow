#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include <SDL_image.h>
#include "Tile.h"



// This class will load all the necessary things required for the game.
// Also, this class will contain the GAME LOOP
namespace apocalypsenow {

	extern SDL_Renderer* g_renderer;
	extern std::fstream errorfile;
	extern std::ifstream test;
	
	
	// Screens constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	// Level Constants
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;

	class Renderer
	{
	private:
		// Screen dimensions

		SDL_Event m_event;
	
		SDL_Window* m_window;
				
		// if this flag is set to true, the game has ended.
		bool m_exit;
	
	public:

		// Initializes member variables.
		Renderer();

		// Deallocates memory in the member variable (Pointers)
		~Renderer();
	
		// Initializes all the necessary modules.
		bool init();

		void update();


		// test function.
		void test();

		void test_loadLevel();

		void test_displaylevel();


		void render();

		//handles all the input events
		void handleEvents();

		//returns m_exit
		bool getExit() const;

		//Execute init, update and render.
		void execute();
	
	};

}
#endif // !_RENDERER_H_
