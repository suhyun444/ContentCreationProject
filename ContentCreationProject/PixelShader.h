#pragma once

#include "Shader.h"
#include <wrl.h>

using Microsoft::WRL::ComPtr;

#include "Texture.h"
#include <vector>
#include <map>

class PixelShader : public Shader
{
public:
	PixelShader();
	PixelShader(std::wstring filename);
	PixelShader(std::wstring filename, std::string entry, std::string profile);
	~PixelShader();

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext) override;

	bool CreateSamplerState(ID3D11Device* device);
	void BindSamplerState(ID3D11DeviceContext* deviceContext);

	bool LoadTexture(ID3D11Device* device, std::wstring filename);
	void BindTextures(ID3D11DeviceContext* deviceContext, std::string frameName);

	ID3D11PixelShader* GetPixelShader() { return pixelShader.Get(); }

private:
	ComPtr<ID3D11PixelShader> pixelShader;

	std::map<std::string,Texture> textures;
	ComPtr<ID3D11SamplerState> samplerState;
};
