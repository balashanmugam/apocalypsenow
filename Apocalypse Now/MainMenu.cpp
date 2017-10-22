#include "MainMenu.h"

apocalypsenow::MainMenu::MainMenu(GameState * state_)
{
}

apocalypsenow::MainMenu::MainMenu()
{
}

apocalypsenow::MainMenu::~MainMenu()
{
}

void apocalypsenow::MainMenu::init()
{
	m_playButton.setType(ButtonType::PLAY);
	m_playButton.setPosition(320 - 50, 240 - 20);
}

void apocalypsenow::MainMenu::setState(GameState state_)
{
	m_state = state_;
}

void apocalypsenow::MainMenu::render()
{
	m_playButton.render();
}

void apocalypsenow::MainMenu::handleEvent(SDL_Event * e_,GameState* state_)
{
	GameState s = m_playButton.handeEvents(e_);
	*state_ = s;
}
