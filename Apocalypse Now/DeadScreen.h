#pragma once
#include "GameManager.h"
#include "Texture.h"

namespace apocalypsenow {

	extern Texture g_deadScreenTexture;
	class DeadScreen
	{
	public:
		DeadScreen();
		void update();
		void render();
		void DeadScreen::handleEvent(SDL_Event * e_);

	private:

	};
}