#pragma once

#include "Vertex.h"
#include <d3d11.h>
#include <wrl.h>
#include "TransformBuffer.h"
#include <vector>
#include "MathUtil.h"
#include "Delegate.h"
#include "BasicShader.h"
#include "TextureMappingShader.h"
using Microsoft::WRL::ComPtr;
using namespace std;

class Mesh
{
public:
	Mesh();
	Mesh(float _mass);
	virtual ~Mesh();

	Delegate<> collideCallback;
	std::vector<Vector3f> GetVertics();
	virtual void Collide(Mesh* collision);
	virtual bool InitializeBuffers(ID3D11Device* device) = 0;
	virtual bool InitializeBuffers(ID3D11Device* device, std::wstring textureFileName) = 0;

	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

	virtual void BindBuffers(ID3D11DeviceContext* deviceContext);
	virtual void DrawBuffers(ID3D11DeviceContext* deviceContext);

	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);

	Vector3f& Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3f position);

	Vector3f& Rotation() { return rotation; }
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3f rotation);

	Vector3f& Scale() { return scale; }
	void SetScale(float x, float y, float z);
	void SetScale(Vector3f scale);

	void SetCollisionScale(float x, float y, float z);
	void SetCollisionScale(Vector3f scale);
	
	void SetMass(float mass);
	float Mass() { return mass; }

	void SetTag(string tag);
	string Tag() { return tag; }

protected:
	MeshShader* meshShader;
	int vertexCount;				// 정점 개수.
	ComPtr<ID3D11Buffer> vertexBuffer;		// 정점 버퍼.
	ComPtr<ID3D11InputLayout> inputLayout; // 입력 레이아웃.

	vector<std::pair<float,float>> verticsRadians;
	Vector3f collisionScale;
	// 트랜스폼 버퍼.
	TransformBuffer transform;

	// 트랜스폼 데이터.
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Vector3f velocity;
	float mass;
	std::string curAnimationState;
	string tag;
};
