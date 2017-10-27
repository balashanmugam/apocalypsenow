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
	m_playButton.setPosition((SCREEN_WIDTH/2 )- 50, (SCREEN_HEIGHT/2) - 10);


	m_quitButton.setType(ButtonType::QUIT);
	m_quitButton.setPosition((SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) + 20);


}

void apocalypsenow::MainMenu::setState(GameState state_)
{
	m_state = state_;
}

void apocalypsenow::MainMenu::render()
{
	g_mainMenuTexture.render(0, 0);

	m_playButton.render();
	//m_instructionButton.render();
	m_quitButton.render();


}

void apocalypsenow::MainMenu::handleEvent(SDL_Event * e_,GameState* state_)
{
	GameState s = m_playButton.handleEvents(e_);
	*state_ = s;
	s = m_quitButton.handleEvents(e_);

}
