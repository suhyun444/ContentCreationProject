#include "MeshHandler.h"
void MeshHandler::RenderBuffer(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i]->SetIsLeft(deviceContext, unitBuffer);
		meshs[i]->RenderBuffers(deviceContext);
	}
}
void MeshHandler::UpdateBuffer(ID3D11DeviceContext* deviceContext)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i]->UpdateBuffers(deviceContext);
	}
}
void MeshHandler::Add(Mesh* mesh)
{
	meshs.push_back(mesh);
}
