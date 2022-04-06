#include "CollisionHandler.h"
#include <iostream>
#include <random>

CollisionHandler::CollisionHandler()
{

}

void CollisionHandler::Add(Mesh* mesh)
{
	meshs.push_back(mesh);
}
void CollisionHandler::BoardPhase()
{
	for (int i = 0; i < meshs.size() - 1; i++)
	{
		for (int j = i + 1; j < meshs.size(); j++)
		{
			if (meshs[i]->Mass() == 0 && meshs[j]->Mass() == 0)continue;
			Collide(meshs[i], meshs[j]);
		}
	}
}
void CollisionHandler::Collide(Mesh* mesh1, Mesh* mesh2)
{
	std::vector<Vector3f> mesh1Vertics = mesh1->GetVertics();
	std::vector<Vector3f> mesh2Vertics = mesh2->GetVertics();

	std::vector<Vector3f> axes;
	for (int i = 0; i < mesh1Vertics.size(); i++)
		axes.push_back(mesh1Vertics[i] - mesh1Vertics[(i + 1) % mesh1Vertics.size()]);
	for (int i = 0; i < mesh2Vertics.size(); i++)
		axes.push_back(mesh2Vertics[i] - mesh2Vertics[(i + 1) % mesh2Vertics.size()]);

	float separation = 999999;
	int verticesCount;
	float minSeparation = 999999;
	Vector3f MTV = Vector3f::Zero;
	for (int ia = 0;ia<axes.size();ia++)
	{
		float ra = 0;
		verticesCount = mesh1Vertics.size();
		for (int i = 0; i < verticesCount; i++)
		{
			Vector3f centerToVertex = mesh1Vertics[i] - mesh1->Position();
			float cur = axes[ia].Dot(centerToVertex);
			ra = max(ra, cur);
		}

		float rb = 0;
		verticesCount = mesh2Vertics.size();
		for (int i = 0; i < verticesCount; i++)
		{
			Vector3f centerToVertex = mesh2Vertics[i] - mesh2->Position();
			float cur = -axes[ia].Dot(centerToVertex);
			if (cur > rb)
			{
				rb = cur;
			}
		}
		Vector3f t = mesh1->Position() - mesh2->Position();
		float distance = fabsf(axes[ia].Dot(t));
		if (distance >= ra + rb)
		{
			return;
		}
		separation = distance - (ra + rb);
		if (separation < minSeparation)
		{
			minSeparation = separation;
			MTV = t;
		}
	}
	std::cout << "Collision" << rand() % 100 << "\n";
}