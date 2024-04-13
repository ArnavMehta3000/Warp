#pragma once
#include <Warp/Common/StandardTypes.h>
#include <chrono>

namespace Warp
{
	class Timer
	{
		using ClockType = std::chrono::high_resolution_clock;
		
		Timer()
			: m_startTime(ClockType::now())
			, m_deltaTime(0.0f)
		{
			m_lastTime = m_startTime;
		}

		void Tick()
		{
			ClockType::time_point currentTime = ClockType::now();
			m_deltaTime = std::chrono::duration<Types::f32>(currentTime - m_lastTime).count();
			m_lastTime = currentTime;
		}

		inline Types::f32 GetDeltaTime() const
		{
			return m_deltaTime;
		}

		inline Types::f32 GetElapsedTime() const
		{
			return std::chrono::duration<Types::f32>(ClockType::now() - m_startTime).count();
		}

		inline Types::f32 GetFPS() const
		{
			return 1.0f / m_deltaTime;
		}
	private:
		ClockType::time_point m_startTime;
		ClockType::time_point m_lastTime;
		Types::f32            m_deltaTime;
	};
}