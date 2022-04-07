#pragma once
#include "Mesh.h"
//#include "BasicShader.h"
class Quad : public Mesh
{
public:
	Quad();
	~Quad();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device) override;
	bool InitializeBuffers(ID3D11Device* device, std::wstring textureFileName) override;

private:
	BasicShader basicShader;
};