#pragma once
#include <vector>
#include <string>
class AnimationState
{
public:
	//spriteName / frameRate
	AnimationState(std::string frames[],int frameRates[]);
	~AnimationState();
	std::vector<std::pair<std::string, int>> frames;
	
};

