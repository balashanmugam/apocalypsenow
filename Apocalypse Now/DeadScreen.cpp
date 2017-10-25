#include "DeadScreen.h"

apocalypsenow::DeadScreen::DeadScreen()
{
}

void apocalypsenow::DeadScreen::update()
{
	// no update
}

void apocalypsenow::DeadScreen::render()
{
	g_deadScreenTexture.render(0, 0);
}
void apocalypsenow::DeadScreen::handleEvent(SDL_Event * e_)
{

}
