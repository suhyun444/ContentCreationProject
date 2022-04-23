#include "AnimationState.h"
AnimationState::AnimationState(std::string frameNames[], int frameRates[])
{
	int size = sizeof(frameRates) / sizeof(frameRates[0]);
	for (int i = 0; i < size ; i++)
	{
		frames.push_back({ frameNames[i],frameRates[i] });
	}
}
AnimationState::~AnimationState()
{

}