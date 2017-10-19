#include "Renderer.h"
#include "Protagonist.h"
#include "Bullet.h"


namespace apocalypsenow
{

	// Global timer
	Timer timeelapsed;

	// Test protagonist
	Protagonist hero(40,40);
	Bullet b[999];

	int g_bulletIndex = 0;

	// Test Textures
	Texture g_protagonistTextureTop;
	Texture g_protagonistTextureBot;
	Texture g_protagonistTextureLeft;
	Texture g_protagonistTextureRight;

	// bullet textures
	Texture g_bulletTextureRight;
	Texture g_bulletTextureLeft;
	Texture g_bulletTextureTop;
	Texture g_bulletTextureBot;


	// global variables;
	Texture g_tileTexture;
	Texture g_blockTileTexture;

	SDL_Renderer* g_renderer;
	std::fstream errorfile;
	//Texture g_protagonistTexture;
	SDL_Rect g_camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// Protagonist Sprites clips
	SDL_Rect g_protagonistClips[PROT_WALKING_DIRECTION][PROT_TOTAL_FRAMES];

	SDL_Rect g_bulletClip;
	SDL_Rect g_tileClip[TILE_TYPES];
	SDL_Rect g_blockTileClip;

	Tile* tiles[TILE_TOTAL];

	//Multithreading. LOL

}
//Constructor
apocalypsenow::Renderer::Renderer()
{
	m_exit = false;
	apocalypsenow::errorfile.open("errorFile.txt");
}

// Loads the subsystems, creates window, apocalypsenow::Renderer ...
bool apocalypsenow::Renderer::init()
{
	bool success = true;


	// Initializes SDL subsystem.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		success = false;
		errorfile << SDL_GetError();
	}

	//Creates a Window where every other thing takes place.
	m_window = SDL_CreateWindow("Apocalypse Now",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	

	if (m_window == NULL)
	{
		success = false;
		errorfile << "Window creation failed " << std::endl;
	}

	//Creates a apocalypsenow::Renderer using the pre created Window
	g_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_renderer == nullptr)
	{
		success = false;
		errorfile << "apocalypsenow::Renderer creation failed" << std::endl;
	}

	// Init the IMG subsystem.
	int image_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	int image_inits = IMG_Init(image_flags);
	
	if ((image_inits &  image_flags) != image_flags)
	{
		success = false;
		errorfile << "Error in initialising image flags subsystem." << std::endl;
		errorfile << IMG_GetError << std::endl;
	}
		

	//Init the Font subsystem.
	if (TTF_Init() != 0)
	{
		success = false;
		errorfile << "TTF subsytem loading failed." << std::endl;
		errorfile << TTF_GetError() << std::endl;
	}

	//Clears the screen
	SDL_SetRenderDrawColor(g_renderer, 255,255, 255, 255);
	SDL_RenderClear(g_renderer);
	return success;
}



void apocalypsenow::Renderer::test_loadLevel()
{
	if (!g_tileTexture.loadTexture("resources/images/test/Map2.png"))
		errorfile << "Fail in loading test tile" << std::endl;

	if (!g_blockTileTexture.loadTexture("resources/images/test/Map3.png"))
		errorfile << "Fail in block texture tile" << std::endl;

	if (!g_protagonistTextureTop.loadTexture("resources/images/test/test_sprite_top.png"))
		errorfile << "TEXTURE LOADING FAILED: Unable to load Sprite sheet of character walk." << std::endl;
	if (!g_protagonistTextureBot.loadTexture("resources/images/test/test_sprite_bot.png"))
		errorfile << "TEXTURE LOADING FAILED: Unable to load Sprite sheet of character walk." << std::endl;
	if (!g_protagonistTextureLeft.loadTexture("resources/images/test/test_sprite_left.png"))
		errorfile << "TEXTURE LOADING FAILED: Unable to load Sprite sheet of character walk." << std::endl;
	if (!g_protagonistTextureRight.loadTexture("resources/images/test/test_sprite_right.png"))
		errorfile << "TEXTURE LOADING FAILED: Unable to load Sprite sheet of character walk." << std::endl;


	if (!g_bulletTextureRight.loadTexture("resources/images/test/bulletf_right.png"))
		errorfile << "BULLET TEXTURE LAODING FAILED: Unable to load sprite sheet of bullet." << std::endl;
	if (!g_bulletTextureLeft.loadTexture("resources/images/test/bulletf_left.png"))
		errorfile << "BULLET TEXTURE LAODING FAILED: Unable to load sprite sheet of bullet." << std::endl;
	if (!g_bulletTextureTop.loadTexture("resources/images/test/bulletf_top.png"))
		errorfile << "BULLET TEXTURE LAODING FAILED: Unable to load sprite sheet of bullet." << std::endl;
	if (!g_bulletTextureBot.loadTexture("resources/images/test/bulletf_bot.png"))
		errorfile << "BULLET TEXTURE LAODING FAILED: Unable to load sprite sheet of bullet." << std::endl;


	// Clipping each frame of the protagonist. //current working for one Direction.
	for (auto j = 0; j < PROT_WALKING_DIRECTION; j++)
	{
		for (auto i = 0; i < PROT_TOTAL_FRAMES; i++)
		{
			g_protagonistClips[j][i].x = i * PROT_WIDTH;
			g_protagonistClips[j][i].y = 0;
			g_protagonistClips[j][i].h = PROT_HEIGHT;
			g_protagonistClips[j][i].w = PROT_WIDTH;
		}
	}
	std::ifstream testmap("test.map");
	
	//Tile* tiles[TILE_TOTAL];
	int x = 0;
	int y = 0;

	if (testmap.fail() == true)
	{
		errorfile << "File Loading failed: Unable to load file." << std::endl;	
	}
	// load map.
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		int tileType = -1;
	
		testmap >> tileType;
		
		if (testmap.fail())
		{
			errorfile << "File reading error: Unexpected end of file." << std::endl;
			break;
		}

		// Check if it is a valid tile.
		if ((tileType >= 0 && tileType < TILE_TYPES) || tileType == TILE_BLOCK)
		{
			tiles[i] = new Tile(x, y, tileType);

		}

		// Next horizontal tile location		
		x += TILE_WIDTH;
		
		// if the tile reaches the end of the level width.
		if (x >= LEVEL_WIDTH)
		{
			x = 0;
			y += TILE_HEIGHT;
		}

	}

	// Now clip
	g_tileClip[TILE_TOPLEFT].x = 0;
	g_tileClip[TILE_TOPLEFT].y = 0;
	g_tileClip[TILE_TOPLEFT].h = TILE_WIDTH;
	g_tileClip[TILE_TOPLEFT].w = TILE_HEIGHT;

	g_tileClip[TILE_LEFT].x = 0;
	g_tileClip[TILE_LEFT].y = 80;
	g_tileClip[TILE_LEFT].h = TILE_WIDTH;
	g_tileClip[TILE_LEFT].w = TILE_HEIGHT;

	g_tileClip[TILE_BOTLEFT].x = 0;
	g_tileClip[TILE_BOTLEFT].y = 160;
	g_tileClip[TILE_BOTLEFT].h = TILE_WIDTH;
	g_tileClip[TILE_BOTLEFT].w = TILE_HEIGHT;
	
	g_tileClip[TILE_TOP].x = 80;
	g_tileClip[TILE_TOP].y = 0;
	g_tileClip[TILE_TOP].h = TILE_WIDTH;
	g_tileClip[TILE_TOP].w = TILE_HEIGHT;

	g_tileClip[TILE_MID].x = 80;
	g_tileClip[TILE_MID].y = 80;
	g_tileClip[TILE_MID].h = TILE_WIDTH;
	g_tileClip[TILE_MID].w = TILE_HEIGHT;

	g_tileClip[TILE_BOT].x = 80;
	g_tileClip[TILE_BOT].y = 160;
	g_tileClip[TILE_BOT].h = TILE_WIDTH;
	g_tileClip[TILE_BOT].w = TILE_HEIGHT;

	g_tileClip[TILE_TOPRIGHT].x = 160;
	g_tileClip[TILE_TOPRIGHT].y = 0;
	g_tileClip[TILE_TOPRIGHT].h = TILE_WIDTH;
	g_tileClip[TILE_TOPRIGHT].w = TILE_HEIGHT;

	g_tileClip[TILE_RIGHT].x = 160;
	g_tileClip[TILE_RIGHT].y = 80;
	g_tileClip[TILE_RIGHT].h = TILE_WIDTH;
	g_tileClip[TILE_RIGHT].w = TILE_HEIGHT;

	g_tileClip[TILE_BOTRIGHT].x = 160;
	g_tileClip[TILE_BOTRIGHT].y = 160;
	g_tileClip[TILE_BOTRIGHT].h = TILE_WIDTH;
	g_tileClip[TILE_BOTRIGHT].w = TILE_HEIGHT;

	g_blockTileClip.x = 0;
	g_blockTileClip.y = 0;
	g_blockTileClip.h = TILE_HEIGHT;
	g_blockTileClip.w = TILE_WIDTH;

	g_bulletClip.x = 0;
	g_bulletClip.y = 0;
	g_bulletClip.h = 25;
	g_bulletClip.w = 25;

	testmap.close();

	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		tiles[i]->render(g_camera);
	}

	SDL_RenderPresent(g_renderer);

}
void apocalypsenow::Renderer::test_displaylevel()
{


}
void apocalypsenow::Renderer::update()
{
	hero.update();
	for(auto i = 0;i < g_bulletIndex;i++)
		b[i].update();
}

void apocalypsenow::Renderer::refreshLevel()
{
	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		tiles[i]->render(g_camera);
	}

	//SDL_RenderPresent(g_renderer);
}

// Will handle close and keyboard press events.
void apocalypsenow::Renderer::handleEvents()
{
	
	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
		{
			//exits.
			m_exit = true;
			
		}
		else if (m_event.type == SDL_KEYDOWN && m_event.key.repeat == 0)
		{
			switch (m_event.key.keysym.sym)
			{
			case SDLK_SPACE:
				b[g_bulletIndex].fireBullet(hero.getBox().x, hero.getBox().y, hero.getDirection());
				g_bulletIndex++;
				if (g_bulletIndex >= 999)
					g_bulletIndex = 0;
				break;
			}
		}
		// hero.
		hero.handleEvents(m_event);
	}

	
}

void apocalypsenow::Renderer::cleanup()
{
	errorfile.close();

}
apocalypsenow::Renderer::~Renderer()
{
	SDL_DestroyWindow(m_window);
	
	m_window = NULL;
	g_renderer = NULL;
}

bool apocalypsenow::Renderer::getExit() const
{
	return m_exit;
}

// Renders all the important textures and stuffs.
void apocalypsenow::Renderer::render()
{
	refreshLevel();
	for (auto i = 0; i < g_bulletIndex; i++)
		b[i].render();
	hero.render(g_camera);
	hero.setCamera(g_camera);
	SDL_RenderPresent(g_renderer);

}

void apocalypsenow::Renderer::execute()
{
	init();
	test_loadLevel();

	while (this->getExit() != true)
	{
		update();
		render();
		handleEvents();
	} 
	cleanup();
}




