#include "AnimationState.h"
AnimationState::AnimationState()
{

}
AnimationState::AnimationState(std::string frameNames[], float frameRates[])
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