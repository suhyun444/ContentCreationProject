#pragma once
#include "Entity.h"
#include "Quad.h"
#include "GroundChecker.h"
#include "Camera.h"
enum class PlayerState
{
	Idle,
	Walk,
	Attack1,
	Attack2,
	Attack3
};
class Player : public Entity
{
public:
	Player();
	~Player();
	void Update(float deltaTime) override;
	void UpdateVelocity(int x, float deltaTime);
	void Jump();
	void GroundCheck();
	void HeadCheck();
	bool GetIsLeft() { return isLeft; }
	void Attack();
	GroundChecker groundChecker;
	GroundChecker headChecker;
	Quad hitbox;
	QuadUV heart[3];
	Camera* camera;
	void Collide(Mesh* mesh) override;
private:
	Vector3f prevPosition;
	int jumpCount = 2;
	
	int attackType;
	float attackTerm;


	PlayerState curState;
	std::map<PlayerState, AnimationState> animationState;
	AnimationState idleState;
	AnimationState walkState;
	AnimationState attack1State;
	AnimationState attack2State;
	AnimationState attack3State;
	void InitAnimationState();
	void ChangeAnimationState(PlayerState nextState);
};

