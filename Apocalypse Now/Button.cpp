#include "Button.h"

apocalypsenow::Button::Button()
{
	m_type = ButtonType::PLAY;
}


apocalypsenow::Button::~Button()
{
}

void apocalypsenow::Button::setType(ButtonType type_)
{
	m_type = type_;
}

void apocalypsenow::Button::setPosition(int x_, int y_)
{
	m_point.x = x_;
	m_point.y = y_;
}

apocalypsenow::GameState apocalypsenow::Button::handleEvents(SDL_Event * e)
{
	GameState change = GameState::MENU;
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		// get mouse states and co-ordinates.
		int x, y;
		SDL_GetMouseState(&x, &y);

		// to check if there is a click inside the mouse region.
		bool inside = true;
		if (x < m_point.x)
			inside = false;
		else if (x > m_point.x + BUTTON_WIDTH)
			inside = false;
		else if (y < m_point.y)
			inside = false;
		else if (y > m_point.y + BUTTON_HEIGHT)
			inside = false;

		// if on the outside.
		if (!inside)
		{
			m_state = ButtonState::MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				m_state = ButtonState::MOUSE_HOVER;
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_state = ButtonState::MOUSE_DOWN;
				switch(m_type)
				{
				case ButtonType::PLAY:
					change = GameState::PLAYING;
					break;
				}	
				break;
			case SDL_MOUSEBUTTONUP:
			default:
				m_state = ButtonState::MOUSE_OUT;
			}
		}	
	}
	return change;
}

void apocalypsenow::Button::render()
{
	switch (m_type)
	{
	case PLAY:
		switch(	m_state)
		{
		case MOUSE_DOWN:
			g_playDownTexture.render(m_point.x, m_point.y);
			break;
		case MOUSE_HOVER:
			g_playHoverTexture.render(m_point.x, m_point.y);
			break;
		case MOUSE_OUT:
			g_playOutTexture.render(m_point.x, m_point.y);
			break;
		}
		break;
	case INSTRUCTIONS:
		switch(m_state)
		{
		case MOUSE_DOWN:
			g_instructionDownTexture.render(m_point.x, m_point.y);
			break;
		case MOUSE_HOVER:
			g_instructionHoverTexture.render(m_point.x, m_point.y);
			break;
		case MOUSE_OUT:
			g_instructionOutTexture.render(m_point.x, m_point.y);
			break;
		}
		break;
	case QUIT:
		switch (m_state)
		{
		case MOUSE_DOWN:
			g_quitDownTexture.render(m_point.x, m_point.y);
			break;
		case MOUSE_HOVER:
			g_quitHoverTexture.render(m_point.x, m_point.y);
			break;
		case MOUSE_OUT:
			g_quitOutTexture.render(m_point.x, m_point.y);
			break;
		}
		break;

	}
}
