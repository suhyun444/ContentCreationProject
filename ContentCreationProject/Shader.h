#pragma once

#include <string>
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Shader
{
protected:
	std::wstring filename;
	std::string entry;
	std::string profile;

	ComPtr<ID3DBlob> shaderBuffer;
public:
	Shader();
	Shader(std::wstring filename);
	Shader(std::wstring filename, std::string entry, std::string profile);
	virtual ~Shader();

	virtual bool Compile(ID3D11Device* device) = 0;
	virtual bool Create(ID3D11Device* device) = 0;
	virtual void Bind(ID3D11DeviceContext* deviceContext) = 0;

	std::wstring FileName() { return filename; }
	std::string Entry() { return entry; }
	std::string Profile() { return profile; }

	ID3DBlob* ShaderBuffer() { return shaderBuffer.Get(); }

};

