#pragma once
#include "QuadUV.h"
#include "Raycast.h"
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
private:
	float thinkTime;
	float thinkDelay;

	bool isLeft = true;
	float animationTime;
	int animationIndex;
	bool isAttack = false;
	CrabState curState;
	std::map<CrabState, AnimationState> animationState;
	AnimationState idleState;
	AnimationState walkState;
	AnimationState attackState;
	AnimationState deadState;
	void InitAnimationState();
	void ChangeAnimationState(CrabState nextState);
};

