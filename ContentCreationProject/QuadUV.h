#pragma once
#include "Mesh.h"
#include "TextureMappingShader.h"
#include "AnimationState.h"

class QuadUV : public Mesh
{
public:
	QuadUV();
	~QuadUV();

	void SetAnimationState(string name);
	// 정점 버퍼 초기화 함수 오버라이딩.
	bool InitializeBuffers(ID3D11Device* device) override;
	bool InitializeBuffers(ID3D11Device* device, std::vector<std::wstring> textureFileNames) override;
private:
	void BindBuffers(ID3D11DeviceContext* deviceContext) override;
	TextureMappingShader textureMappingShader;
};