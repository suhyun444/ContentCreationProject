#include "Crab.h"
#include <iostream>
Crab::Crab()
{
	isTrigger = true;
	position = Vector3f(3.0f, 1.0f, 0.0f);
	scale = Vector3f(1.5f, 1.5f, 1.0f);
	collisionScale = Vector3f(0.6f, 0.6f, 0.0f);
	collisionOffset = Vector3f(0.0f, -0.46f, 0.0f);
	
	animationTime = 0.0f;
	animationIndex = 0;
	curState = CrabState::Idle;
	curAnimationState = "CrabIdle1.png";
	InitAnimationState();

	thinkTime = 0.0f;
	thinkDelay = 3.0f;

	hitbox.SetScale(0.0f, 0.0f, 1.0f);
	hitbox.SetCollisionScale(0.7f, 0.5f, 1.0f);
	hitbox.SetIsEnable(false);
	hitbox.SetIsTrigger(true);
	hitbox.SetTag("EnemyAttack");
}
Crab::~Crab()
{

}
void Crab::Update(float deltaTime)
{
	deltaTime /= 1000;
	animationTime += deltaTime;
	unBeatTime += deltaTime;

	velocity.y -= 1.0f;
	velocity.y = max(velocity.y, -2.5f);

	if (!isAttack && !isDead)
	{
		if (player->Position().x < position.x)isLeft = true;
		else isLeft = false;

		position = position + Vector3f(velocity.x, velocity.y, 0) * deltaTime;
	}

	animationTime += deltaTime;
	if (animationTime > animationState[curState].frames[animationIndex].second)
	{
		animationTime = 0.0f;
		curAnimationState = animationState[curState].frames[animationIndex].first;
		if (++animationIndex == animationState[curState].frames.size())
		{
			if (curState == CrabState::Dead)isEnable = false;
			if (animationState[curState].isLoop)
				animationIndex %= animationState[curState].frames.size();
			else
			{
				isAttack = false;
				animationIndex--;
			}
		}
	}
	
	float distance = sqrt(pow(player->Position().x - position.x,2) + pow(player->Position().y - position.y, 2));
	if (distance < 3 || isAttack)
	{
		attackTime += deltaTime;
		if (attackTime > attackDelay)
		{
			isAttack = true;
			attackTime = 0.0f;
			ChangeAnimationState(CrabState::Attack);
		}
	}

	if (velocity.x != 0 && curState == CrabState::Idle && !isAttack && !isDead)
	{
		ChangeAnimationState(CrabState::Walk);
	}
	if (velocity.x == 0 && curState == CrabState::Walk && !isAttack && !isDead)
	{
		ChangeAnimationState(CrabState::Idle);
	}
	if (!isAttack && curState == CrabState::Attack && !isDead)
	{
		ChangeAnimationState(CrabState::Idle);
	}
	thinkTime -= deltaTime;
	GroundCheck();
	if (thinkTime < 0)
	{
		thinkTime = rand() % 2 + 3;
		Think();
	}

	if (isAttack && 0.5f < attackTime && attackTime < 0.6f)hitbox.SetIsEnable(true);
	else hitbox.SetIsEnable(false);

	hitbox.SetPosition(position.x + 0.3f * ((isLeft) ? -1 : 1), position.y - 0.4f, 0.0f);
}
void Crab::GroundCheck()
{
	Mesh* collision = Raycast::instance->Hit(position.x + (0.6f * velocity.x), position.y - 0.8f);
	if (collision == NULL)
	{
		velocity.x *= -1;
		thinkTime = rand() % 2 + 3;
		return;
	}
}
void Crab::SetPlayer(Player* player)
{
	this->player = player;
}
void Crab::Collide(Mesh* collision)
{
	if (collision->Tag() == "PlayerAttack")
	{
		if (unBeatTime > 0.5f)
		{
			unBeatTime = 0.0f;
			hp--;
			if (hp == 0)
			{
				ChangeAnimationState(CrabState::Dead);
				isDead = true;
			}
		}
	}
}

void Crab::Think()
{
	int type = rand() % 3;
	if (type == 0) velocity.x = -1;
	else if(type == 1)velocity.x = 1;
	else
	{
		thinkTime = 3.0f;
		velocity.x = 0.0f;
	}
}
void Crab::SetIsLeft(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer)
{
	Matrix4f unitInfo;
	if (!isLeft)unitInfo.Get(0,0) = 1;
	if (unBeatTime < 0.1f)unitInfo.Get(1, 1) = 1;
	deviceContext->UpdateSubresource(unitBuffer, NULL, nullptr, &unitInfo, 0, 0);
	deviceContext->VSSetConstantBuffers(2, 1, &unitBuffer);
}

void Crab::InitAnimationState()
{
	for (int i = 1; i < 6; i++)
	{
		idleState.frames.push_back({ "CrabIdle" + to_string(i) + ".png",0.17f });
	}
	animationState.insert({ CrabState::Idle,idleState });

	for (int i = 1; i < 10; i++)
	{
		walkState.frames.push_back({ "CrabWalk" + to_string(i) + ".png",0.12f });
	}
	animationState.insert({ CrabState::Walk,walkState });

	for (int i = 1; i < 13; i++)
	{
		attackState.frames.push_back({ "CrabAttack" + to_string(i) + ".png",0.1f });
	}
	attackState.isLoop = false;
	animationState.insert({ CrabState::Attack,attackState });

	for (int i = 1; i < 19; i++)
	{
		deadState.frames.push_back({ "CrabDead" + to_string(i) + ".png",0.06f });
	}
	deadState.isLoop = false;
	animationState.insert({ CrabState::Dead,deadState });
}
string GetFirstTextureName(CrabState state)
{
	if (state == CrabState::Walk)
		return "CrabWalk1.png";
	if (state == CrabState::Idle)
		return "CrabIdle1.png";
	if (state == CrabState::Attack)
		return "CrabAttack1.png";
	if (state == CrabState::Dead)
		return "CrabDead1.png";
}
void Crab::ChangeAnimationState(CrabState nextState)
{
	curState = nextState;
	curAnimationState = GetFirstTextureName(nextState);
	animationTime = 0.0f;
	animationIndex = 0;
}