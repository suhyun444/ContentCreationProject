#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include <string>
class MeshShader
{
public:
	virtual bool Compile(ID3D11Device* device, std::vector<std::wstring> textureFileNames) = 0;
	virtual bool Compile(ID3D11Device* device) = 0;
	virtual bool Create(ID3D11Device* device) = 0;
	virtual void Bind(ID3D11DeviceContext* deviceContext, std::string frameName) = 0;

	ID3DBlob* ShaderBuffer();

protected:
	VertexShader vertexShader;
	PixelShader pixelShader;
};

