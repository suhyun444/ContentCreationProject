#pragma once
#include <vector>
#include <string>
class AnimationState
{
public:
	bool isLoop = true;
	//spriteName / frameRate
	AnimationState();
	AnimationState(std::string frames[],float frameRates[]);
	~AnimationState();
	std::vector<std::pair<std::string, float>> frames;
	
};

