#pragma once
#include "QuadUV.h"
class Entity : public QuadUV
{
public:
	Entity();
	~Entity();
	void SetIsLeft(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer) override;
	virtual void Update(float deltaTime);
protected:
	bool isLeft = true;
	bool isAttack = false;

	float unBeatTime = 2.0;
	int curHp = 3;

	float animationTime;
	int animationIndex;

	float attackTime = 0.0f;
	float attackDelay = 3.0f;
};

