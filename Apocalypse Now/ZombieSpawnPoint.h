#pragma once
#include "GameObject.h"
namespace apocalypsenow {

	class ZombieSpawnPoint:public GameObject
	{

	private:

		
	public:

		void update();
		void render();
		void placeSpawnPoint(int x_, int y_);
		ZombieSpawnPoint();
		~ZombieSpawnPoint();
	};
}