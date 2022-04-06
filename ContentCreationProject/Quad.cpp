#include "Quad.h"

Quad::Quad()
{
}

Quad::~Quad()
{
}

bool Quad::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // ���� ������ �����.
    // ����(Vertex) �迭.
    // �޼� ��ǥ��.
    Vertex vertices[] =
    {
        Vertex(-0.5f, -0.5f, 0.0f),
        Vertex(-0.5f, 0.5f, 0.0f),
        Vertex(0.5f, 0.5f, 0.0f),
        Vertex(-0.5f, -0.5f, 0.0f),
        Vertex(0.5f, 0.5f, 0.0f),
        Vertex(0.5f, -0.5f, 0.0f)
    };
    verticsRadians.push_back({ atan2f(vertices[0].y, vertices[0].x),	sqrtf((vertices[0].x * vertices[0].x) + (vertices[0].y * vertices[0].y)) });
    verticsRadians.push_back({ atan2f(vertices[1].y, vertices[1].x),	sqrtf((vertices[1].x * vertices[1].x) + (vertices[1].y * vertices[1].y)) });
    verticsRadians.push_back({ atan2f(vertices[2].y, vertices[2].x),	sqrtf((vertices[2].x * vertices[2].x) + (vertices[2].y * vertices[2].y)) });
    verticsRadians.push_back({ atan2f(vertices[5].y, vertices[5].x),	sqrtf((vertices[5].x * vertices[5].x) + (vertices[5].y * vertices[5].y)) });

    // ������ ����.
    vertexCount = ARRAYSIZE(vertices);

    // ���� ���� �����.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(vertices); // �󸶸�ŭ ������.
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ������ ���۷� �� ���̴�.
    vertexBufferDesc.CPUAccessFlags = 0; // ������ �ø��� ���� CPU�� GPU ������ �� �ְ� �ұ�? �츮�� ���� ���ؼ� �ڵ��� �� ������ �����ϰ� ���� ��. 0�� �� �����ϰ�.
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ������ ���.
    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = vertices;

    // ���� ���� ����.
    HRESULT result = device->CreateBuffer(
        &vertexBufferDesc,
        &vertexBufferData,
        vertexBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� ���� ���� ����", L"����", 0);
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    // �Է� ���̾ƿ� ����.
    result = device->CreateInputLayout(
        layout,
        ARRAYSIZE(layout),
        vertexShaderBuffer->GetBufferPointer(),
        vertexShaderBuffer->GetBufferSize(),
        inputLayout.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�Է� ���̾ƿ� ���� ����", L"����", 0);
        return false;
    }

    // ��� ����.
    if (transform.Create(device) == false)
    {
        return false;
    }

    return true;
}