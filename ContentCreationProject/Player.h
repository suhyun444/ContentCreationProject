#pragma once
#include "QuadUV.h"
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
class Player : public QuadUV
{
public:
	Player();
	~Player();
	void SetIsLeft(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer) override;
	void Update(float deltaTime);
	void UpdateVelocity(int x);
	void Jump();
	void GroundCheck();
	bool GetIsLeft() { return isLeft; }
	void Attack();
	GroundChecker groundChecker;
	Quad hitbox;
	QuadUV heart[3];
	Camera* camera;
	void Collide(Mesh* mesh) override;
private:
	Vector3f prevPosition;
	float animationTime;
	bool canJump = false;
	bool isLeft = false;
	bool isAttack = false;
	
	int attackType;
	float attackTime;
	float attackDelay;
	float attackTerm;

	int curHp = 3;
	float unBeatTime = 2.0;

	int animationIndex;
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

