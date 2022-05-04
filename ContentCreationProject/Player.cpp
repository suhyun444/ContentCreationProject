#include "Player.h"
#include <iostream>

Player::Player()
{
	animationTime = 0.0f;
	animationIndex = 0;
	curState = PlayerState::Idle;
	curAnimationState = "PlayerIdle1.png";
	InitAnimationState();
	attackTime = 0.0f;
	attackType = 0;
	attackDelay = 0.38f;
	attackTerm = 0.7f;
	groundChecker.InitializeCollideCallback(std::bind(&Player::GroundCheck, this));
}
Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	deltaTime /= 1000;
	attackTime += deltaTime;
	if (attackTime > attackTerm)
		attackType = 0;

	position = position + Vector3f(velocity.x, velocity.y, 0) * deltaTime;
	if (velocity.x < 0 && !isLeft && !isAttack)
	{
		isLeft = true;
	}
	else if (velocity.x > 0 && isLeft && !isAttack)
	{
		isLeft = false;
	}

	animationTime += deltaTime;
	if (animationTime > animationState[curState].frames[animationIndex].second)
	{
		animationTime = 0.0f;
		curAnimationState = animationState[curState].frames[animationIndex].first;
		if (++animationIndex == animationState[curState].frames.size())
		{
			if (animationState[curState].isLoop)
				animationIndex %= animationState[curState].frames.size();
			else
			{
				isAttack = false;
				animationIndex--;
			}
		}
	}
	if (velocity.x != 0 && curState != PlayerState::Walk && !isAttack)
	{
		ChangeAnimationState(PlayerState::Walk);
	}
	else if (velocity.x == 0 && curState != PlayerState::Idle && !isAttack)
	{
		ChangeAnimationState(PlayerState::Idle);
	}
	
	
	groundChecker.SetPosition(Vector3f(position.x, position.y - scale.y / 2, 0));
}
void Player::Attack()
{
	isAttack = true;
	if (attackType == 0)
	{
		ChangeAnimationState(PlayerState::Attack1);
		attackType = 1;
		attackTime = 0.0f;
	}
	if (attackType == 1 && attackTime > attackDelay)
	{
		ChangeAnimationState(PlayerState::Attack2);
		attackType = 2;
		attackTime = 0.0f;
	}
	if (attackType == 2 && attackTime > attackDelay)
	{
		ChangeAnimationState(PlayerState::Attack3);
		attackType = 3;
		attackTime = 0.0f;
	}
}
void Player::UpdateVelocity(int x)
{
	velocity.x = x * ((isAttack) ? 0.3f : 1.0f);
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
std::string GetFirstTextureName(PlayerState state)
{
	if (state == PlayerState::Walk)
		return "PlayerWalk1.png";
	if (state == PlayerState::Idle)
		return "PlayerIdle1.png";
	if (state == PlayerState::Attack1)
		return "PlayerAttack1.png";
	if (state == PlayerState::Attack2)
		return "PlayerAttack7.png";
	if (state == PlayerState::Attack3)
		return "PlayerAttack13.png";
}
void Player::ChangeAnimationState(PlayerState nextState)
{
	curState = nextState;
	curAnimationState = GetFirstTextureName(nextState);
	animationTime = 0.0f;
	animationIndex = 0;
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

	for (int i = 1; i < 7; i++)
	{
		attack1State.frames.push_back({ "PlayerAttack" + to_string(i) + ".png",0.06f });
	}
	attack1State.isLoop = false;
	animationState.insert({ PlayerState::Attack1,attack1State });

	for (int i = 7; i < 13; i++)
	{
		attack2State.frames.push_back({ "PlayerAttack" + to_string(i) + ".png",0.06f });
	}
	attack2State.isLoop = false;
	animationState.insert({ PlayerState::Attack2,attack2State });

	for (int i = 13; i < 18; i++)
	{
		attack3State.frames.push_back({ "PlayerAttack" + to_string(i) + ".png",0.06f });
	}
	attack3State.isLoop = false;
	animationState.insert({ PlayerState::Attack3,attack3State });
}