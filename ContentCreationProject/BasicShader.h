#pragma once
#include "MeshShader.h"

class BasicShader : public MeshShader
{
public:
	bool Compile(ID3D11Device* device, std::vector<std::wstring> textureFileNames) override;
	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext, std::string frameName) override;
};

