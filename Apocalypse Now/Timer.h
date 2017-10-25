#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include "GameManager.h"

namespace apocalypsenow
{
	class Timer
	{
	private:

		// Start of the time.
		Uint32 m_start;

		// Time until paused.
		Uint32 m_pause;

		// States of the Timer.
		bool m_isPaused; 
		bool m_isStarted;

	public:
		// Init all
		Timer();

		//Functions of the timer.
		void start();
		void stop();
		void pause();
		void unpause();

		// Returns the time until paused.
		Uint32 getTicks();
		
		// Returns the state of the timer.
		bool isStarted();
		bool isPaused();


	};
}
#endif