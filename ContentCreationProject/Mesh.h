#pragma once

#include "Vertex.h"
#include <d3d11.h>
#include <wrl.h>
#include "TransformBuffer.h"
#include <vector>
#include "MathUtil.h"
//#include "MeshShader.h"
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

	std::vector<Vector3f> GetVertics();
	// ���� ���� �Լ�, = �������̽�.
	virtual bool InitializeBuffers(ID3D11Device* device) = 0;
	virtual bool InitializeBuffers(ID3D11Device* device, std::wstring textureFileName) = 0;

	// Render = (Bind + Draw)
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

	// ��ο�/������Ʈ ���� ���� �Լ�.
	virtual void BindBuffers(ID3D11DeviceContext* deviceContext);
	virtual void DrawBuffers(ID3D11DeviceContext* deviceContext);

	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);

	// Getter / Setter
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


protected:
	MeshShader* meshShader;
	int vertexCount;				// ���� ����.
	ComPtr<ID3D11Buffer> vertexBuffer;		// ���� ����.
	ComPtr<ID3D11InputLayout> inputLayout; // �Է� ���̾ƿ�.

	vector<std::pair<float,float>> verticsRadians;
	Vector3f collisionScale;
	// Ʈ������ ����.
	TransformBuffer transform;

	// Ʈ������ ������.
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Vector3f velocity;
	float mass;
	std::string curAnimationState;
};
