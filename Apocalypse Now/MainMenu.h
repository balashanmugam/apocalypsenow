#pragma once
#include <SDL.h>
#include "GameManager.h"
#include "Button.h"
namespace apocalypsenow
{
	extern Texture g_playOutTexture;
	extern Texture g_playHoverTexture;
	extern Texture g_playDownTexture;

	extern Texture g_instructionOutTexture;
	extern Texture g_instructionHoverTexture;
	extern Texture g_instructionDownTexture;

	extern Texture g_quitOutTexture;
	extern Texture g_quitHoverTexture;
	extern Texture g_quitDownTexture;

	class MainMenu
	{
	private:
		Button m_playButton;
		Button m_instructionButton;
		Button m_quitButton;
		GameState m_state;
	public:
		MainMenu(GameState* state_);

		MainMenu();
		~MainMenu();

		// probably not needed.
		void init();

		// set the State of the Renderer.
		void setState(GameState state_);

		void render();
		// all it does is change the state.
		void handleEvent(SDL_Event* e_, GameState* state_);
	};
}