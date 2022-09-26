#pragma once
#include "Matrix4f.h"
#include "Vector3f.h"
#include <d3d11.h>

#include <wrl.h>
using Microsoft::WRL::ComPtr;

class Camera
{
public:
	Camera();
	Camera(float fov, float width, float height, float zNear, float zFar);
	Camera(Camera& other);
	~Camera() = default;

	void MoveForward(float velocity);
	void MoveRight(float velocity);
	void MoveUp(float velocity);

	void Yaw(float angle);
	void Pitch(float angle);

	bool CreateBuffer(ID3D11Device* device);
	void BindBuffer(ID3D11DeviceContext* deviceContext);

	float AspectRatio() { return (float)width / (float)height; }
	void SetAspectRatio(float width, float height);

	Matrix4f View() { return viewMatrix; }
	Matrix4f Projection() { return projectionMatrix; }

	Vector3f Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3f position);
	void UpdateCamera();

private:
	float fov;						
	float width;					
	float height;					
	float zNear;					
	float zFar;				

	Matrix4f projectionMatrix;

	float yaw = 0.0f;			
	float pitch = 0.0f;		

	Vector3f position;			

	Vector3f forward;			
	Vector3f right;			
	Vector3f up;		

	Vector3f look;			

	Matrix4f viewMatrix;	

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	ComPtr<ID3D11Buffer> cameraBuffer;
};