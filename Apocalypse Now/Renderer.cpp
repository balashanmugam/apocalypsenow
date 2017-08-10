#include "Renderer.h"

using namespace apocalypsenow;

namespace apocalypsenow
{
	// global variables;
	Texture g_tileTexture;
	SDL_Rect g_tileClip[TILE_TYPES];
	SDL_Renderer* g_renderer;
	std::fstream errorfile;

}
//Constructor
Renderer::Renderer()
{
	m_exit = false;
	errorfile.open("errorFile.txt");
}

// Loads the subsystems, creates window, renderer ...
bool Renderer::init()
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

	//Creates a renderer using the pre created Window
	g_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_renderer == nullptr)
	{
		success = false;
		errorfile << "Renderer creation failed" << std::endl;
	}

	// Init the IMG subsystem.
	int image_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	int image_inits = IMG_Init(image_flags);
	
	if (image_inits&image_flags != image_flags)
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


	return success;
}

void Renderer::update()
{
	// handles input too!
}

// Renders all the important textures and stuffs.
void Renderer::render()
{
	
	//Clears the screen
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	test();
	test_loadLevel();

	//Updates the screen.
	SDL_RenderPresent(g_renderer);
}

void Renderer::test()
{
	Texture t;
	t.loadTexture("resources/images/test/test_joey.jpg");
	t.render(t.getWidth()/4, t.getHeight()/4);
	t.free();
	SDL_RenderClear(g_renderer);


}

void Renderer::test_loadLevel()
{
	if (!g_tileTexture.loadTexture("resources/images/test/test_tiles.png"))
		errorfile << "Fail in loading test tile" << std::endl;

	std::ifstream testmap("test.map");
	
	Tile* tiles[TILE_TOTAL];
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
		if (tileType >= 0 && tileType <= TILE_TYPES)
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
	g_tileClip[TILE_RED].x = 0;
	g_tileClip[TILE_RED].y = 0;
	g_tileClip[TILE_RED].h = TILE_WIDTH;
	g_tileClip[TILE_RED].w = TILE_HEIGHT;

	g_tileClip[TILE_GREEN].x = 0;
	g_tileClip[TILE_GREEN].y = 80;
	g_tileClip[TILE_GREEN].h = TILE_WIDTH;
	g_tileClip[TILE_GREEN].w = TILE_HEIGHT;

	g_tileClip[TILE_BLUE].x = 0;
	g_tileClip[TILE_BLUE].y = 160;
	g_tileClip[TILE_BLUE].h = TILE_WIDTH;
	g_tileClip[TILE_BLUE].w = TILE_HEIGHT;
	
	g_tileClip[TILE_TOPLEFT].x = 80;
	g_tileClip[TILE_TOPLEFT].y = 0;
	g_tileClip[TILE_TOPLEFT].h = TILE_WIDTH;
	g_tileClip[TILE_TOPLEFT].w = TILE_HEIGHT;

	g_tileClip[TILE_LEFT].x = 80;
	g_tileClip[TILE_LEFT].y = 80;
	g_tileClip[TILE_LEFT].h = TILE_WIDTH;
	g_tileClip[TILE_LEFT].w = TILE_HEIGHT;

	g_tileClip[TILE_BOTLEFT].x = 80;
	g_tileClip[TILE_BOTLEFT].y = 160;
	g_tileClip[TILE_BOTLEFT].h = TILE_WIDTH;
	g_tileClip[TILE_BOTLEFT].w = TILE_HEIGHT;

	g_tileClip[TILE_TOP].x = 160;
	g_tileClip[TILE_TOP].y = 0;
	g_tileClip[TILE_TOP].h = TILE_WIDTH;
	g_tileClip[TILE_TOP].w = TILE_HEIGHT;

	g_tileClip[TILE_MID].x = 160;
	g_tileClip[TILE_MID].y = 80;
	g_tileClip[TILE_MID].h = TILE_WIDTH;
	g_tileClip[TILE_MID].w = TILE_HEIGHT;

	g_tileClip[TILE_BOT].x = 160;
	g_tileClip[TILE_BOT].y = 160;
	g_tileClip[TILE_BOT].h = TILE_WIDTH;
	g_tileClip[TILE_BOT].w = TILE_HEIGHT;

	g_tileClip[TILE_TOPRIGHT].x = 240;
	g_tileClip[TILE_TOPRIGHT].y = 0;
	g_tileClip[TILE_TOPRIGHT].h = TILE_WIDTH;
	g_tileClip[TILE_TOPRIGHT].w = TILE_HEIGHT;

	g_tileClip[TILE_RIGHT].x = 240;
	g_tileClip[TILE_RIGHT].y = 80;
	g_tileClip[TILE_RIGHT].h = TILE_WIDTH;
	g_tileClip[TILE_RIGHT].w = TILE_HEIGHT;

	g_tileClip[TILE_BOTRIGHT].x = 240;
	g_tileClip[TILE_BOTRIGHT].y = 160;
	g_tileClip[TILE_BOTRIGHT].h = TILE_WIDTH;
	g_tileClip[TILE_BOTRIGHT].w = TILE_HEIGHT;

	testmap.close();

	SDL_Rect camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	for (auto i = 0; i < TILE_TOTAL; i++)
	{
		tiles[i]->render(camera);
	}

}
void Renderer::test_displaylevel()
{


}

// Will handle close and keyboard press events.
void Renderer::handleEvents()
{
	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
		{
			//exits.
			m_exit = true;
		}
	}

	
}


Renderer::~Renderer()
{
	SDL_DestroyWindow(m_window);
	
	m_window = NULL;
	g_renderer = NULL;
}

bool Renderer::getExit() const
{
	return m_exit;
}

void Renderer::execute()
{
	init();
	while (this->getExit() != true)
	{
		render();
		update();
		handleEvents();
	}
}