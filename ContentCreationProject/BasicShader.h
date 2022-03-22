#pragma once

#include "VertexShader.h"
#include "PixelShader.h"

class BasicShader
{
private:
	static VertexShader vertexShader;
	static PixelShader pixelShader;
	static PixelShader colorPixelShader;

public:
	static bool Compile(ID3D11Device* device);
	static bool Create(ID3D11Device* device);
	static void BindVertexShader(ID3D11DeviceContext* deviceContext);
	static void BindWhiteShader(ID3D11DeviceContext* deviceContext);
	static void BindColorShader(ID3D11DeviceContext* deviceContext);
	static ID3DBlob* ShaderBuffer();
};

