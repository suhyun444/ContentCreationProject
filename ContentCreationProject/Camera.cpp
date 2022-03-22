#include "Camera.h"

Camera::Camera()
	: Camera(70.0f, 1280.0f, 800.0f, 0.1f, 1000.0f)
{
}

Camera::Camera(float fov, float width, float height, float zNear, float zFar)
	: fov(fov), width(width), height(height), zNear(zNear), zFar(zFar),
	position(0.0f, 0.0f, -5.0f),
	look(0.0f, 0.0f, 0.0f),
	up(0.0f, 1.0f, 0.0f),
	right(1.0f, 0.0f, 0.0f),
	forward(0.0f, 0.0f, 1.0f)
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

Camera::Camera(Camera& other)
	: Camera(other.fov, other.width, other.height, other.zNear, other.zFar)
{
}

void Camera::MoveForward(float velocity)
{
	position += forward * velocity;
}

void Camera::MoveRight(float velocity)
{
	position += right * velocity;
}

void Camera::MoveUp(float velocity)
{
	position += up * velocity;
}

void Camera::Yaw(float angle)
{
	yaw += angle;
}

void Camera::Pitch(float angle)
{
	pitch += angle;
}

bool Camera::CreateBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC cameraBufferDesc;
	memset(&cameraBufferDesc, 0, sizeof(cameraBufferDesc));
	cameraBufferDesc.ByteWidth = sizeof(Matrix4f) * 2;
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cameraBufferDesc.CPUAccessFlags = 0;
	cameraBufferDesc.MiscFlags = 0;

	Matrix4f cameraMatrix = viewMatrix * projectionMatrix;

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = &cameraMatrix;

	HRESULT result = device->CreateBuffer(
		&cameraBufferDesc,
		&data,
		cameraBuffer.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"ī�޶� ���� ���� ����", L"����", 0);
		throw std::exception("ī�޶� ���� ���� ����");
		return false;
	}

	return true;
}

void Camera::BindBuffer(ID3D11DeviceContext* deviceContext)
{
	Matrix4f cameraMatrix = viewMatrix * projectionMatrix;

	deviceContext->UpdateSubresource(cameraBuffer.Get(), NULL, nullptr, &cameraMatrix, 0, 0);
	deviceContext->VSSetConstantBuffers(1, 1, cameraBuffer.GetAddressOf());
}

void Camera::SetAspectRatio(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Camera::SetPosition(float x, float y, float z)
{
	this->position = Vector3f(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetPosition(Vector3f position)
{
	this->position = position;
	UpdateViewMatrix();
}

void Camera::UpdateCamera()
{
	Matrix4f rotationMatrix = Matrix4f::Rotation(pitch, yaw, 0.0f);

	// ī�޶� �ٶ�����ϴ� ��ġ ����.
	look = rotationMatrix * Vector3f::Forward;
	look = look.Normalized();	// ����ȭ.

	// 3��Ī ī�޶�.
	right = rotationMatrix * Vector3f::Right;
	up = rotationMatrix * Vector3f::Up;
	forward = rotationMatrix * Vector3f::Forward;

	// �ٶ�����ϴ� ��ġ ����.
	look = position + look;
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// �� ��ȯ ��� �����.
	viewMatrix = Matrix4f::LookAt(position, look, up);
}

void Camera::UpdateProjectionMatrix()
{
	// ���� ��ȯ ��� �����.
	projectionMatrix = Matrix4f::Perspective(fov, width, height, zNear, zFar);
}
