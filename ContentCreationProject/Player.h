#pragma once
#include "QuadUV.h"
#include "GroundChecker.h"

enum class PlayerState
{
	Idle,
	Walk,
	Attack1,
	Attack2
};
class Player : public QuadUV
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void UpdateVelocity(int x);
	void Jump();
	void GroundCheck();
	bool GetIsLeft() { return isLeft; }
	GroundChecker groundChecker;
private:
	float animationTime;
	bool canJump = false;
	bool isLeft = false;

	int animationIndex;
	PlayerState curState;
	std::map<PlayerState, AnimationState> animationState;
	AnimationState idleState;
	AnimationState walkState;
	void InitAnimationState();
};

