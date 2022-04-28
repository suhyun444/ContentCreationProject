#pragma once
#include "Mesh.h"
#include "TextureMappingShader.h"
#include "AnimationState.h"

class QuadUV : public Mesh
{
public:
	QuadUV();
	~QuadUV();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device) override;
	bool InitializeBuffers(ID3D11Device* device, std::vector<std::wstring> textureFileNames) override;
private:
	void BindBuffers(ID3D11DeviceContext* deviceContext) override;
	TextureMappingShader textureMappingShader;
};