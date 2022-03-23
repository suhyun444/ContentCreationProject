#include "TransformBuffer.h"


bool TransformBuffer::Create(ID3D11Device* device)
{
	//��� ����
	D3D11_BUFFER_DESC transformBufferDesc;
	ZeroMemory(&transformBufferDesc, sizeof(transformBufferDesc));
	transformBufferDesc.ByteWidth = sizeof(Matrix4f);
	transformBufferDesc.CPUAccessFlags = 0;
	transformBufferDesc.MiscFlags = 0;
	transformBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	//���� ���
	transformMatrix = Matrix4f::Identity();

	//������ ���
	D3D11_SUBRESOURCE_DATA transformBufferData;
	ZeroMemory(&transformBufferData, sizeof(transformBufferData));
	transformBufferData.pSysMem = &transformMatrix;


	//���� ����
	HRESULT result = device->CreateBuffer(
		&transformBufferDesc,
		&transformBufferData,
		constantBuffer.GetAddressOf()
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"��� ���� ���� ����", L"����", 0);
		return false;
	}
	return true;
}

void TransformBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
	//��� ������ ������Ʈ
	deviceContext->UpdateSubresource(constantBuffer.Get(), 0, NULL, &transformMatrix, 0, 0);

	//��� �����Ͱ� ��� ���� ���ε�
	deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
}