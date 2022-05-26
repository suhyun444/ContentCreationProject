#pragma once
#include <vector>
#include "Mesh.h"

using namespace std;
class CollisionHandler
{
public:
	CollisionHandler();
	vector<Mesh*> meshs;
	void Add(Mesh* mesh);
	void BoardPhase();
	void Collide(Mesh* mesh1, Mesh* mesh2);
	void Compression(float x,float y,float size,vector<Mesh*> meshVector);
	Mesh* Raycast(float x, float y);
};

