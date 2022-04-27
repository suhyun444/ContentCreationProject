#include "Player.h"
Player::Player()
{
	curAnimationState = "Player.png";
	groundChecker.InitializeCollideCallback(std::bind(&Player::GroundCheck, this));
}
Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	deltaTime /= 1000;
	position = position + Vector3f(velocity.x, velocity.y, 0) * deltaTime;
}
void Player::UpdateVelocity(int x)
{
	velocity.x = x;
	velocity.y -= 1.0f;
	velocity.y = max(velocity.y, -3.0f);
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