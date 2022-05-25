#pragma once
#include "QuadUV.h"
enum class PuzzleStoneState
{
	Idle,
	OnHit
};
class PuzzleStone : public QuadUV
{
public:
	PuzzleStone();
	~PuzzleStone();
	void Update(float deltaTime);
	QuadUV* walls[2];
	void Collide(Mesh* collision) override;

private:
	float unBeatTime = 2.0f;
	PuzzleStoneState curState;
	float animationTime;
	int animationIndex;
	void InitAnimationState();
	void ChangeAnimationState(PuzzleStoneState nextState);
	std::map<PuzzleStoneState, AnimationState> animationState;
	AnimationState idleState;
	AnimationState onHitState;


};

