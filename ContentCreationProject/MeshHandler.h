#pragma once
#include "Mesh.h"
#include <vector>

using namespace std;

class MeshHandler
{
private:
	vector<Mesh*>meshs;
public:
	void RenderBuffer(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer);
	void UpdateBuffer(ID3D11DeviceContext* deviceContext);
	void Add(Mesh* mesh);
};

