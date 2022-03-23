#pragma once

#include "Vertex.h"
#include <d3d11.h>
#include <wrl.h>
#include "TransformBuffer.h"

using Microsoft::WRL::ComPtr;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	// ���� ���� �Լ�, = �������̽�.
	virtual bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) = 0;

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


protected:
	int vertexCount;				// ���� ����.
	ComPtr<ID3D11Buffer> vertexBuffer;		// ���� ����.
	ComPtr<ID3D11InputLayout> inputLayout; // �Է� ���̾ƿ�.

	// Ʈ������ ����.
	TransformBuffer transform;

	// Ʈ������ ������.
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
};
