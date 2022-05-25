#include "puzzleStone.h"
#include <iostream>
PuzzleStone::PuzzleStone()
{
	scale = Vector3f(1.0f, 1.0f, 1.0f);
	collisionScale = Vector3f(1.0f, 0.5f, 1.0f);
	position = Vector3f(3.0f, -2.0f, 0.0f);
	isTrigger = true;
	tag = "puzzleStone";
	curAnimationState = "PuzzleStone1.png";
	curState = PuzzleStoneState::Idle;
	animationIndex = 0;
	animationTime = 0.0f;
	InitAnimationState();
}
PuzzleStone::~PuzzleStone()
{

}
void PuzzleStone::Update(float deltaTime)
{
	deltaTime /= 1000;
	unBeatTime += deltaTime;
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
				ChangeAnimationState(PuzzleStoneState::Idle);
			}
		}
	}
}
void PuzzleStone::Collide(Mesh* collision)
{
	if (collision->Tag() == "PlayerAttack")
	{
		if (unBeatTime > 1.0f)
		{
			unBeatTime = 0.0f;
			ChangeAnimationState(PuzzleStoneState::OnHit);
			for (int i = 0; i < 2; i++)walls[i]->SetIsEnable(!walls[i]->IsEnable());
		}
	}
}
void PuzzleStone::InitAnimationState()
{
	for (int i = 1; i < 2; i++)
	{
		idleState.frames.push_back({ "PuzzleStone" + to_string(i) + ".png",0.1f });
		idleState.frames.push_back({ "PuzzleStone" + to_string(i) + ".png",0.1f});
	}
	animationState.insert({ PuzzleStoneState::Idle,idleState });

	for (int i = 2; i < 11; i++)
	{
		onHitState.frames.push_back({ "PuzzleStone" + to_string(i) + ".png",0.08f });
	}
	onHitState.isLoop = false;
	animationState.insert({ PuzzleStoneState::OnHit,onHitState });
}
string GetFirstTextureName(PuzzleStoneState state)
{
	if (state == PuzzleStoneState::Idle)
		return "PuzzleStone1.png";
	if (state == PuzzleStoneState::OnHit)
		return "PuzzleStone2.png";
}
void PuzzleStone::ChangeAnimationState(PuzzleStoneState nextState)
{
	curState = nextState;
	curAnimationState = GetFirstTextureName(nextState);
	animationTime = 0.0f;
	animationIndex = 0;
}
