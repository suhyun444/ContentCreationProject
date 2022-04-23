#pragma once
#include "QuadUV.h"
class Player : public QuadUV
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void UpdateVelocity(int x);
	void Jump();
private:
	bool isJump = false;
};

