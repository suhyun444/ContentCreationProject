#pragma once
#include "Mesh.h"
class Quad : public Mesh
{
public:
	Quad();
	~Quad();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;

private:

};