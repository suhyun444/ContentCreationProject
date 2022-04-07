#include "BasicShader.h"

bool BasicShader::Compile(ID3D11Device* device, std::wstring textureFileName)
{
	return false;
}
bool BasicShader::Compile(ID3D11Device* device)
{
	vertexShader = VertexShader(L"..//shaders//BasicVS.hlsl", "main", "vs_5_0");
	pixelShader = PixelShader(L"..//shaders//BasicPS.hlsl", "main", "ps_5_0");
	if (vertexShader.Compile(device) == false)
	{
		return false;
	}
	if (pixelShader.Compile(device) == false)
	{
		return false;
	}
	return true;
}
bool BasicShader::Create(ID3D11Device* device)
{

	if (vertexShader.Create(device) == false)
	{
		return false;
	}
	if (pixelShader.Create(device) == false)
	{
		return false;
	}
	return true;
}
void BasicShader::Bind(ID3D11DeviceContext* deviceContext)
{
	vertexShader.Bind(deviceContext);
	pixelShader.Bind(deviceContext);
}
