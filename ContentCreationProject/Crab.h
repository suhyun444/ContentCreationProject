#pragma once
#include "Entity.h"
#include "Raycast.h"
#include "Player.h"

enum class CrabState
{
	Idle,
	Walk,
	Attack,
	Dead
};
class Crab : public Entity
{
public:
	Crab();
	~Crab();
	void Update(float deltaTime);
	void Think();
	void GroundCheck();
	void SetPlayer(Player* player);
	Quad hitbox;
	void Collide(Mesh* collision) override;
private:
	Player* player;
	float recognizeRange = 10.0f;


	float thinkTime;
	float thinkDelay;

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

