#include "QuadUV.h"
#include "VertexUV.h"

QuadUV::QuadUV()
{
	meshShader = &textureMappingShader;
}

QuadUV::~QuadUV()
{
}
void QuadUV::SetAnimationState(string name)
{
	curAnimationState = name;
}
bool QuadUV::InitializeBuffers(ID3D11Device* device)
{
	return false;
}
bool QuadUV::InitializeBuffers(ID3D11Device* device, std::vector<std::wstring> textureFileNames)
{
	if (meshShader->Compile(device, textureFileNames) == false)
	{
		return false;
	}
	if (meshShader->Create(device) == false)
	{
		return false;
	}
	ID3DBlob* vertexShaderBuffer = meshShader->ShaderBuffer();

	VertexUV vertices[] =
	{
		VertexUV(Vector3f(-0.5f, -0.5f, 0.0f), Vector2f(0.0f, 1.0f)),
		VertexUV(Vector3f(-0.5f, 0.5f, 0.0f), Vector2f(0.0f, 0.0f)),
		VertexUV(Vector3f(0.5f, 0.5f, 0.0f), Vector2f(1.0f, 0.0f)),

		VertexUV(Vector3f(-0.5f, -0.5f, 0.0f), Vector2f(0.0f, 1.0f)),
		VertexUV(Vector3f(0.5f, 0.5f, 0.0f), Vector2f(1.0f, 0.0f)),
		VertexUV(Vector3f(0.5f, -0.5f, 0.0f), Vector2f(1.0f, 1.0f))
	};
	verticsRadians.push_back({ atan2f(vertices[0].y, vertices[0].x),	sqrtf((vertices[0].x * vertices[0].x) + (vertices[0].y * vertices[0].y)) });
	verticsRadians.push_back({ atan2f(vertices[1].y, vertices[1].x),	sqrtf((vertices[1].x * vertices[1].x) + (vertices[1].y * vertices[1].y)) });
	verticsRadians.push_back({ atan2f(vertices[2].y, vertices[2].x),	sqrtf((vertices[2].x * vertices[2].x) + (vertices[2].y * vertices[2].y)) });
	verticsRadians.push_back({ atan2f(vertices[5].y, vertices[5].x),	sqrtf((vertices[5].x * vertices[5].x) + (vertices[5].y * vertices[5].y)) });
	vertexCount = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0; 
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;

	HRESULT result = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		vertexBuffer.GetAddressOf()
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"정점 버퍼 생성 실패", L"오류", 0);
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} 
	};

	result = device->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		inputLayout.GetAddressOf()
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"입력 레이아웃 생성 실패", L"오류", 0);
		return false;
	}

	if (transform.Create(device) == false)
	{
		return false;
	}

	return true;
}

void QuadUV::BindBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride = sizeof(VertexUV);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 

	transform.Bind(deviceContext);
}