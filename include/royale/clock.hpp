#pragma once

#include <chrono>

namespace royale
{
	class Clock
	{
		bool mRunning{};
		std::chrono::steady_clock::time_point mLastUpdate{};

	public:
		Clock() = default;

		void startClock();
		void stopClock();
		bool isRunning();

		// get time since the last call of this function in seconds
		double getTimeSinceLastCall();
	};
}