#include "clock.hpp"

namespace royale
{
	void Clock::startClock()
	{
		mLastUpdate = std::chrono::high_resolution_clock::now();
		mRunning = true;
	}

	void Clock::stopClock()
	{
		mRunning = false;
	}

	bool Clock::isRunning()
	{
		return mRunning;
	}

	double nanoToSeconds(double nanoseconds)
	{
		double seconds = nanoseconds / 1'000'000'000.0;
		return seconds;
	}

	double Clock::getTimeSinceLastCall()
	{

		auto currentTime = std::chrono::high_resolution_clock::now();
		auto diff = currentTime - mLastUpdate;
		auto diffSeconds = nanoToSeconds(diff.count());
		mLastUpdate = currentTime;

		return diffSeconds;
	}
}