#pragma once
#include <Warp/Common/StandardTypes.h>
#include <chrono>

namespace Warp
{
	template <typename Real = Types::f32>
	class Timer
	{
		using ClockType = std::chrono::high_resolution_clock;
	public:
		Timer() : m_deltaTime(0.0f) { }

		static Timer Create()
		{
			Timer t = Timer();
			t.m_startTime = ClockType::now();
			t.m_lastTime = t.m_startTime;
			return t;
		}

		void Tick()
		{
			ClockType::time_point currentTime = ClockType::now();
			m_deltaTime = std::chrono::duration<Real>(currentTime - m_lastTime).count();
			m_lastTime = currentTime;
		}

		inline Real GetDeltaTime() const
		{
			return m_deltaTime;
		}

		inline Real GetElapsedTime() const
		{
			return std::chrono::duration<Real>(ClockType::now() - m_startTime).count();
		}

		inline Real GetFPS() const
		{
			return 1.0f / m_deltaTime;
		}

	private:
		ClockType::time_point m_startTime;
		ClockType::time_point m_lastTime;
		Real            m_deltaTime;
	};
}