#include "Time.h"
#include "SDL.h"

namespace Engine
{
	double Engine::Time::m_DeltaTime = 0;
	int Engine::Time::m_LastTime = 0;
	int Engine::Time::m_NewTime = 0;

	void Time::SetDeltaTime()
	{
		m_NewTime = SDL_GetTicks();
		m_DeltaTime = (m_NewTime - m_LastTime) / 1000.0;
		m_LastTime = m_NewTime;
	}
}