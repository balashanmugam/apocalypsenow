#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Player.h"
namespace apocalypsenow {
	
	const int KEY_HEIGHT = 50;
	const int KEY_WIDTH = 50;

	extern Player hero;
	extern SDL_Rect g_camera;
	extern Texture g_keyTexture;

	class Key : public GameObject
	{
	private:

	public:
		Key();
		~Key();

		void render();

		void spawnAt(int x_ , int y_);

		void update();
	};
}