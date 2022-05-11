#pragma once
#include "CollisionHandler.h"
class Raycast
{
public:
	static Raycast* instance;
	void Initialize();
	CollisionHandler* collisionHandler;
	Raycast();
	~Raycast();
	Mesh* Hit(float x, float y);
};

