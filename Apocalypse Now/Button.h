#pragma once
#include <SDL.h>
#include "Texture.h"
namespace apocalypsenow {


	// Extern textures;
	extern Texture g_playOutTexture;
	extern Texture g_playHoverTexture;
	extern Texture g_playDownTexture;

	extern Texture g_instructionOutTexture;
	extern Texture g_instructionHoverTexture;
	extern Texture g_instructionDownTexture;

	extern Texture g_quitOutTexture;
	extern Texture g_quitHoverTexture;
	extern Texture g_quitDownTexture;

	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 35;
	enum ButtonState
	{
		MOUSE_OUT,
		MOUSE_HOVER,
		MOUSE_DOWN

	};
	enum ButtonType
	{
		PLAY,
		INSTRUCTIONS,
		QUIT
	};
	class Button
	{
	private:
		// Left point position.
		SDL_Point m_point;
		SDL_Rect* clip;
		ButtonState m_state;
		ButtonType m_type;

	public:
		Button();
		~Button();

		void setType(ButtonType type_);
		void setPosition(int x_, int y_);

		// Menu only changes the state. so we return the GameState.
		GameState handleEvents(SDL_Event* e);
		
		void render();
	};
}