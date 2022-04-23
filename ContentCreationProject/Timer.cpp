#include "Timer.h"

Timer::Timer()
{

}
Timer::~Timer()
{

}
bool Timer::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	if (frequency == 0)
	{
		return false;
	}

	ticksPerMs = (float)(frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	return true;
}

void Timer::Frame()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeDifference = (float)(currentTime - startTime);

	frameTime = timeDifference / ticksPerMs;

	startTime = currentTime;

	return;
}

float Timer::GetTime()
{
	return frameTime;
}