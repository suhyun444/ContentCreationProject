#pragma once
#include "QuadUV.h"
#include "GroundChecker.h"

enum class PlayerState
{
	Idle,
	Walk,
	Attack1,
	Attack2,
	Attack3
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
	void Attack();
	GroundChecker groundChecker;
private:
	float animationTime;
	bool canJump = false;
	bool isLeft = false;
	bool isAttack = false;
	
	int attackType;
	float attackTime;
	float attackDelay;
	float attackTerm;

	int animationIndex;
	PlayerState curState;
	std::map<PlayerState, AnimationState> animationState;
	AnimationState idleState;
	AnimationState walkState;
	AnimationState attack1State;
	AnimationState attack2State;
	AnimationState attack3State;
	void InitAnimationState();
	void ChangeAnimationState(PlayerState nestState);
};

