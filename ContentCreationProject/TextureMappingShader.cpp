#include "TextureMappingShader.h"

bool TextureMappingShader::Compile(ID3D11Device* device, std::vector<std::wstring> textureFileNames)
{
	vertexShader = VertexShader(L"..//shaders//TextureMappingVS.hlsl", "main", "vs_5_0");
	//vertexShader = VertexShader(L"shaders//TextureMappingVS.cso", "main", "vs_5_0");
	pixelShader = PixelShader(L"..//shaders//TextureMappingPS.hlsl", "main", "ps_5_0");
	//pixelShader = PixelShader(L"shaders//TextureMappingPS.cso", "main", "ps_5_0");
	if (vertexShader.Compile(device) == false)
	{
		return false;
	}
	if (pixelShader.Compile(device) == false)
	{
		return false;
	}

	for (int i = 0; i < textureFileNames.size(); i++)
	{
		if (pixelShader.LoadTexture(device, textureFileNames[i]) == false)
		{
			return false;
		}
	}
	return true;
}
bool TextureMappingShader::Compile(ID3D11Device* device)
{
	return false;
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

	// 샘플러 스테이트 생성.
	if (pixelShader.CreateSamplerState(device) == false)
	{
		return false;
	}

	return true;
}

void TextureMappingShader::Bind(ID3D11DeviceContext* deviceContext, std::string frameName)
{
	vertexShader.Bind(deviceContext);
	pixelShader.Bind(deviceContext);
	pixelShader.BindTextures(deviceContext,frameName);
	pixelShader.BindSamplerState(deviceContext);
}
