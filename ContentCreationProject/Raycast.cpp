#include "Raycast.h"
#include <iostream>
Raycast* Raycast::instance = NULL;
Raycast::Raycast()
{
	instance = this;
}
Raycast::~Raycast()
{
}
Mesh* Raycast::Hit(float x,float y)
{
	Mesh* mesh = collisionHandler->Raycast(x, y);
	return mesh;
}
void Raycast::Initialize()
{
	instance = this;
}