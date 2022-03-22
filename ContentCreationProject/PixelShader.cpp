#include <d3dcompiler.h>
#include "PixelShader.h"

PixelShader::PixelShader() : Shader()
{

}

PixelShader::PixelShader(std::wstring filename) : Shader(filename)
{
	profile = "ps_5_0";
}

PixelShader::PixelShader(std::wstring filename, std::string entry, std::string profile)
	: Shader(filename, entry, profile)
{

}
PixelShader::~PixelShader()
{

}

bool PixelShader::Compile(ID3D11Device* device)
{
	//ÇÈ¼¿½¦ÀÌ´õ ÄÄÆÄÀÏ
	HRESULT result = D3DCompileFromFile(
		filename.c_str(),
		NULL,
		NULL,
		entry.c_str(),
		profile.c_str(),
		NULL,
		NULL,
		shaderBuffer.GetAddressOf(),
		NULL
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"ÇÈ¼¿½¦ÀÌ´õ ÄÄÆÄÀÏ ½ÇÆÐ", L"¿À·ù", 0);
		return false;
	}
	return true;
}

bool PixelShader::Create(ID3D11Device* device)
{
	//ÇÈ¼¿½¦ÀÌ´õ »ý¼º
	HRESULT result = device->CreatePixelShader(
		shaderBuffer->GetBufferPointer(),
		shaderBuffer->GetBufferSize(),
		nullptr,
		pixelShader.GetAddressOf()
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"ÇÈ¼¿ ½¦ÀÌ´õ »ý¼º ½ÇÆÐ", L"¿À·ù", 0);
		return false;
	}
	return true;
}
void PixelShader::Bind(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShader(pixelShader.Get(), NULL, NULL);
}
