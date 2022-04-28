#include "Player.h"

Player::Player()
{
	curAnimationState = "Player.png";
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