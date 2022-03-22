#include "BasicShader.h"

VertexShader BasicShader::vertexShader = VertexShader(L"..//shaders//BasicVS.hlsl", "main", "vs_5_0");
PixelShader BasicShader::pixelShader = PixelShader(L"..//shaders//BasicPS.hlsl", "main", "ps_5_0");
PixelShader BasicShader::colorPixelShader = PixelShader(L"..//shaders//ColorPS.hlsl", "main", "ps_5_0");

bool BasicShader::Compile(ID3D11Device* device)
{
	if (vertexShader.Compile(device) == false)
	{
		return false;
	}
	if (pixelShader.Compile(device) == false)
	{
		return false;
	}
	if (colorPixelShader.Compile(device) == false)
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
	if (colorPixelShader.Create(device) == false)
	{
		return false;
	}
	return true;
}
void BasicShader::BindVertexShader(ID3D11DeviceContext* deviceContext)
{
	vertexShader.Bind(deviceContext);
}
void BasicShader::BindWhiteShader(ID3D11DeviceContext* deviceContext)
{
	pixelShader.Bind(deviceContext);
}
void BasicShader::BindColorShader(ID3D11DeviceContext* deviceContext)
{
	colorPixelShader.Bind(deviceContext);
}

ID3DBlob* BasicShader::ShaderBuffer()
{
	return vertexShader.ShaderBuffer();
}