#pragma once
#include "QuadUV.h"
#include "GroundChecker.h"

class Player : public QuadUV
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void UpdateVelocity(int x);
	void Jump();
	void GroundCheck();
	GroundChecker groundChecker;
private:
	bool canJump = false;
};

