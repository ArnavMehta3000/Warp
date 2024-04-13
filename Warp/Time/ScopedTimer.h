#pragma once
#include <Warp/Common/StandardTypes.h>
#include <chrono>

namespace Warp
{
	template <typename Real = Types::f32>
	class ScopedTimer
	{
	public:
		using ClockType = std::chrono::high_resolution_clock;

		ScopedTimer(Real* outElapsedTime) 
			: m_startTime(ClockType::now()) 
			, m_outElapsedTime(outElapsedTime)
		{
		}

		~ScopedTimer() { *m_outElapsedTime = GetElapsedTime();}

		inline Real GetElapsedTime() const
		{
			return std::chrono::duration<Real>(ClockType::now() - m_startTime).count();
		}

	private:
		ClockType::time_point m_startTime;
		Real*                 m_outElapsedTime;
	};
}