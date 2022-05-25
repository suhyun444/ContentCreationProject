#include "Entity.h"

Entity::Entity()
{

}
Entity::~Entity()
{

}
void Entity::SetIsLeft(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer)
{
	Matrix4f unitInfo;
	if (isLeft)unitInfo.Get(0, 0) = 1;
	if (unBeatTime < 0.1f)unitInfo.Get(1, 1) = 1;
	deviceContext->UpdateSubresource(unitBuffer, NULL, nullptr, &unitInfo, 0, 0);
	deviceContext->VSSetConstantBuffers(2, 1, &unitBuffer);
}
void Entity::Update(float deltaTime)
{

}