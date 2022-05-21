#include "MeshHandler.h"
bool Compare(Mesh* mesh1, Mesh* mesh2)
{
	return mesh1->SortingOrder() < mesh2->SortingOrder();
}
void MeshHandler::RenderBuffer(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer)
{
	Matrix4f unitInfo;
	deviceContext->UpdateSubresource(unitBuffer, NULL, nullptr, &unitInfo, 0, 0);
	deviceContext->VSSetConstantBuffers(2, 1, &unitBuffer);
	for (int i = 0; i < meshs.size(); i++)
	{
		if (!meshs[i]->IsEnable())continue;
		meshs[i]->SetIsLeft(deviceContext, unitBuffer);
		meshs[i]->RenderBuffers(deviceContext);
	}
}
void MeshHandler::UpdateBuffer(ID3D11DeviceContext* deviceContext)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		if (!meshs[i]->IsEnable())continue;
		meshs[i]->UpdateBuffers(deviceContext);
	}
}
void MeshHandler::Add(Mesh* mesh)
{
	meshs.push_back(mesh);
	sort(meshs.begin(), meshs.end(), Compare);
}
