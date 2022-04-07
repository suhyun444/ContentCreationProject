#include "MeshShader.h"

ID3DBlob* MeshShader::ShaderBuffer()
{
	return vertexShader.ShaderBuffer();
}