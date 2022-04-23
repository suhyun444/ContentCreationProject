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
		separation = (ra + rb) - distance;
		if (separation < minSeparation)
		{
			minSeparation = separation;
			MTV = t;
		}
	}
	float xDiff = fabsf(mesh1->Position().x - mesh2->Position().x);
	float yDiff = fabsf(mesh1->Position().y - mesh2->Position().y);

	//움직이지 않는 물체 한개 정하기
	int type = -1;
	if (mesh1->Mass() == 0)type = 0;
	if (mesh2->Mass() == 0)type = 1;
	if (type == -1) type = (mesh1->Mass() > mesh2->Mass()) ? 0 : 1;
	//가로 절반크기보다 크면 좌우로 밀기
	//세로 절반크기보다 크면 상하로 밀기
	if (type == 0)
	{
		if (xDiff > mesh1->Scale().x / 2)
			MTV.y = 0;
		if(yDiff > mesh1->Scale().y / 2)
			MTV.x = 0;
		MTV.Normalized();
		mesh2->SetPosition(mesh2->Position() - MTV * minSeparation);
	}
	else
	{
		if (xDiff > mesh2->Scale().x / 2)
			MTV.y = 0;
		if (yDiff > mesh2->Scale().y / 2)
			MTV.x = 0;
		MTV.Normalized();
		mesh1->SetPosition(mesh1->Position() + MTV * minSeparation);
	}
}