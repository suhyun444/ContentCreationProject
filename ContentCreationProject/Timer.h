#pragma once
#include <Windows.h>

class Timer
{
private:
	INT64 frequency;
	float ticksPerMs;
	INT64 startTime;
	float frameTime;
public:
	Timer();
	~Timer();

	bool Initialize();
	void Frame();
	float GetTime();
};