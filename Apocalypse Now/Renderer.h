#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"



// This class will load all the necessary things required for the game.
// Also, this class will contain the GAME LOOP
namespace Pong {
	static std::fstream errorfile;
	class Paddle;
	class Timer;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	class Renderer
	{
	private:
		// Screen dimensions

		SDL_Event m_event;
	
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		
		TTF_Font* m_timerFont;

		//Paddles to play.
		Paddle* player1;
		Paddle* player2;
		
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
