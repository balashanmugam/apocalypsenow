#include "Renderer.h"

using namespace apocalypsenow;

namespace apocalypsenow
{
	// global variables;
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

	//Updates the screen.
	SDL_RenderPresent(g_renderer);
}

void Renderer::test()
{
	Texture t;
	t.loadTexture("resources/images/test_joey.jpg");
	t.render(0, 0);
	t.free();
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