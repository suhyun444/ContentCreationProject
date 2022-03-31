#pragma once
#include <vector>
#include "Mesh.h"

using namespace std;
class CollisionHanler
{
	vector<Mesh*> meshs;
	void BoardPhase();
	void Collide(Mesh* mesh1, Mesh* mesh2);
};

