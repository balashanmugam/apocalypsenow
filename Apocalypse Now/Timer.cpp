#include "Timer.h"


apocalypsenow::Timer::Timer()
{
	m_start = 0;
	m_pause = 0;

	m_isStarted = false;
	m_isPaused = false;
}

void apocalypsenow::Timer::start()
{
	m_isStarted = true;

	m_isPaused = false;

	m_start = SDL_GetTicks();

	m_pause = 0;
}

void apocalypsenow::Timer::stop()
{
	m_isStarted = false;

	m_isPaused = false;

	// Clear the time variables.

	m_start = 0;
	m_pause = 0;
}

void apocalypsenow::Timer::pause()
{
	//You can only pause when the timer is running, right?
	if (m_isStarted)
	{
		m_isPaused = true;

		m_pause = SDL_GetTicks() - m_start;
		m_start = 0;

	}
}

void apocalypsenow::Timer::unpause()
{
	if (m_isStarted && m_isPaused)
	{
		
		m_isPaused = false;

		m_start - SDL_GetTicks() - m_pause;
		m_pause = 0;
		
	}
}


Uint32 apocalypsenow::Timer::getTicks()
{
	Uint32 time = 0;
	if (m_isStarted)
	{
		if (m_isPaused)
		{
			time = m_pause;
		}
		else
		{
			time = SDL_GetTicks() - m_start;
		}
	}

	return time;
}

bool apocalypsenow::Timer::isPaused()
{
	return m_isPaused && m_isStarted;
}

bool apocalypsenow::Timer::isStarted()
{
	return m_isStarted;
}