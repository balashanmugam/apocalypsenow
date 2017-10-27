#pragma once
#include <SDL.h>
#include "Texture.h"

namespace apocalypsenow {

	extern Texture g_gameWin;

	class WinScreen
	{
	public:
		WinScreen();
		void update();
		void render();
		void handleEvent(SDL_Event * e_);

	private:

	};
}