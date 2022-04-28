#include "Player.h"
#include <iostream>

Player::Player()
{
	animationTime = 0.0f;
	animationIndex = 0;
	curState = PlayerState::Idle;
	curAnimationState = "PlayerIdle1.png";
	InitAnimationState();
	groundChecker.InitializeCollideCallback(std::bind(&Player::GroundCheck, this));
}
Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	deltaTime /= 1000;
	position = position + Vector3f(velocity.x, velocity.y, 0) * deltaTime;
	if (velocity.x < 0 && !isLeft)
	{
		isLeft = true;
	}
	else if (velocity.x > 0 && isLeft)
	{
		isLeft = false;
	}

	animationTime += deltaTime;
	if (animationTime > animationState[curState].frames[animationIndex].second)
	{
		animationTime = 0.0f;
		curAnimationState = animationState[curState].frames[animationIndex++].first;
		animationIndex %= animationState[curState].frames.size();
	}
	if (velocity.x != 0 && curState != PlayerState::Walk)
	{
		curState = PlayerState::Walk;
		curAnimationState = "PlayerWalk1.png";
		animationTime = 0.0f;
		animationIndex = 0;
	}
	else if (velocity.x == 0 && curState != PlayerState::Idle)
	{
		curState = PlayerState::Idle;
		curAnimationState = "PlayerIdle1.png";
		animationTime = 0.0f;
		animationIndex = 0;
	}
	groundChecker.SetPosition(Vector3f(position.x, position.y - scale.y / 2, 0));
}
void Player::UpdateVelocity(int x)
{
	velocity.x = x;
	velocity.y -= 1.0f;
	velocity.y = max(velocity.y, -2.5f);
}
void Player::Jump()
{
	if (!canJump)return;
	canJump = false;
	velocity.y = 12.0f;
}
void Player::GroundCheck()
{
	canJump = true;
}
void Player::InitAnimationState()
{
	for (int i = 1; i < 9; i++)
	{
		idleState.frames.push_back({"PlayerIdle" + to_string(i) + ".png",0.1f});
	}
	animationState.insert({ PlayerState::Idle,idleState });
	for (int i = 1; i < 10; i++)
	{
		walkState.frames.push_back({ "PlayerWalk" + to_string(i) + ".png",0.1f });
	}
	animationState.insert({ PlayerState::Walk,walkState });
}