#pragma once
#include "Mesh.h"
//#include "BasicShader.h"
class Quad : public Mesh
{
public:
	Quad();
	~Quad();

	// 정점 버퍼 초기화 함수 오버라이딩.
	bool InitializeBuffers(ID3D11Device* device) override;
	bool InitializeBuffers(ID3D11Device* device, std::wstring textureFileName) override;

private:
	BasicShader basicShader;
};