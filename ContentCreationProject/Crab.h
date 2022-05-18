#pragma once
#include "QuadUV.h"
#include "Raycast.h"
#include "Player.h"

enum class CrabState
{
	Idle,
	Walk,
	Attack,
	Dead
};
class Crab : public QuadUV
{
public:
	Crab();
	~Crab();
	void Update(float deltaTime);
	void Think();
	void SetIsLeft(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer) override;
	void GroundCheck();
	void SetPlayer(Player* player);
	Quad hitbox;
	void Collide(Mesh* collision) override;
private:
	Player* player;
	float attackRange = 10.0f;
	float attackTime = 0.0f;
	float attackDelay = 3.0f;

	float unBeatTime = 2.0f;

	int hp = 3;

	float thinkTime;
	float thinkDelay;

	bool isLeft = true;
	float animationTime;
	int animationIndex;
	bool isAttack = false;
	bool isDead = false;
	CrabState curState;
	std::map<CrabState, AnimationState> animationState;
	AnimationState idleState;
	AnimationState walkState;
	AnimationState attackState;
	AnimationState deadState;
	void InitAnimationState();
	void ChangeAnimationState(CrabState nextState);
};

