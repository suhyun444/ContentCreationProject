#pragma once

#include "Shader.h"
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class PixelShader : public Shader
{
private:
	ComPtr<ID3D11PixelShader> pixelShader;
public:
	PixelShader();
	PixelShader(std::wstring filename);
	PixelShader(std::wstring filename, std::string entry, std::string profile);
	~PixelShader();

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext)override;

	ID3D11PixelShader* GetPixelShader() { return pixelShader.Get(); }
};
