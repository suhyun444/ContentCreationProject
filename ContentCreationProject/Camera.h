#pragma once
#include "Matrix4f.h"
#include "Vector3f.h"
#include <d3d11.h>

#include <wrl.h>
using Microsoft::WRL::ComPtr;

// �� ��ȯ. / ���� ��ȯ.
class Camera
{
public:
	Camera();
	Camera(float fov, float width, float height, float zNear, float zFar);
	Camera(Camera& other);
	~Camera() = default;

	// �̵�/ȸ��.
	void MoveForward(float velocity);
	void MoveRight(float velocity);
	void MoveUp(float velocity);

	// Y�� ȸ��.
	void Yaw(float angle);
	// X�� ȸ��.
	void Pitch(float angle);

	// ��� ���� ����/���ε�.
	bool CreateBuffer(ID3D11Device* device);
	void BindBuffer(ID3D11DeviceContext* deviceContext);

	// Getter / Setter.
	// ��Ⱦ��. 
	float AspectRatio() { return (float)width / (float)height; }
	void SetAspectRatio(float width, float height);

	Matrix4f View() { return viewMatrix; }
	Matrix4f Projection() { return projectionMatrix; }

	Vector3f Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3f position);
	void UpdateCamera();

private:
	// ���� ��ȯ ���� ����.
	float fov;						// Field Of View(�þ߰�).
	float width;					// ȭ�� �ʺ�. (ex: 1280)
	float height;					// ȭ�� ����. (ex: 800)
	float zNear;					// �������� z ����� ��ġ.
	float zFar;						// �������� z �� ��ġ.

	Matrix4f projectionMatrix;

	// �� ��ȯ ���� ����.
	float yaw = 0.0f;				// Y�� ȸ�� ��.
	float pitch = 0.0f;				// X�� ȸ�� ��.

	Vector3f position;				// ī�޶� ��ġ.

	Vector3f forward;				// �չ���.
	Vector3f right;					// ������.
	Vector3f up;					// ��.

	Vector3f look;					// �ٶ󺸴� ��ġ.

	Matrix4f viewMatrix;			// ��(ī�޶�) ���.

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	// ��� ���� - ��/���� ��� ���޿� ����.
	ComPtr<ID3D11Buffer> cameraBuffer;
};