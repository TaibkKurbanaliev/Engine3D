#pragma once

namespace Engine
{
	class Time
	{
	public:
		static void SetDeltaTime();
		static double GetDeltaTime() { return m_DeltaTime; }
	private:
		static double m_DeltaTime;
		static int m_LastTime;
		static int m_NewTime;
	};
}