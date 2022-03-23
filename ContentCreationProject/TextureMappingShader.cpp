#include "TextureMappingShader.h"

VertexShader TextureMappingShader::vertexShader = VertexShader(L"..//shaders//TextureMappingVS.hlsl", "main", "vs_5_0");
PixelShader TextureMappingShader::pixelShader = PixelShader(L"..//shaders//TextureMappingPS.hlsl", "main", "ps_5_0");

bool TextureMappingShader::Compile(ID3D11Device* device, std::wstring textureFileName)
{
	if (vertexShader.Compile(device) == false)
	{
		return false;
	}
	if (pixelShader.Compile(device) == false)
	{
		return false;
	}

	// �ؽ��� �ε�.
	if (pixelShader.LoadTexture(device, textureFileName) == false)
	{
		return false;
	}

	return true;
}

bool TextureMappingShader::Create(ID3D11Device* device)
{
	if (vertexShader.Create(device) == false)
	{
		return false;
	}
	if (pixelShader.Create(device) == false)
	{
		return false;
	}

	// ���÷� ������Ʈ ����.
	if (pixelShader.CreateSamplerState(device) == false)
	{
		return false;
	}

	return true;
}

void TextureMappingShader::Bind(ID3D11DeviceContext* deviceContext)
{
	vertexShader.Bind(deviceContext);
	pixelShader.Bind(deviceContext);
	pixelShader.BindTextures(deviceContext);
	pixelShader.BindSamplerState(deviceContext);
}

ID3DBlob* TextureMappingShader::ShaderBuffer()
{
	return vertexShader.ShaderBuffer();
}