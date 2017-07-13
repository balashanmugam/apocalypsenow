#include "Renderer.h"

using namespace Pong;


//Constructor
Renderer::Renderer()
{
	m_exit = false;
	m_timerFont = nullptr;


	errorfile.open("errorFile.txt");
}

// Loads the subsystems, creates window, renderer ...
bool Renderer::init()
{
	bool success = true;

	// Initializes SDL subsystem.
	if (!SDL_Init(SDL_INIT_EVERYTHING))
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

	//Creates a renderer using the pre created Windos.
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
	{
		success = false;
		errorfile << "Renderer creationg failed" << std::endl;
	}

	//Init the Font subsystem.
	if (!TTF_Init())
	{
		success = false;
		errorfile << "TTF subsytem loading failed." << std::endl;
	}
	// Load fonts
	m_timerFont = TTF_OpenFont("Fonts/slkscr.ttf", 18);
	if (m_timerFont == nullptr)
	{
		success = false;
		errorfile << " Font loading Failed" << std::endl;
	}
	return success;
}

void Renderer::update()
{
	// handles input too!
	// Movement of the paddles.
}

// Renders all the important textures and stuffs.
void Renderer::render()
{
	
	//Clears the screen
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);



	//Updates the screen.
	SDL_RenderPresent(m_renderer);
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
	m_renderer = NULL;
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