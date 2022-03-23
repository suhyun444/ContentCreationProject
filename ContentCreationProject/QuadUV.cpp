#include "QuadUV.h"
#include "VertexUV.h"

QuadUV::QuadUV()
{
}

QuadUV::~QuadUV()
{
}

bool QuadUV::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // ���� ������ �����.
    // ����(Vertex) �迭.
    // �޼� ��ǥ��.
    VertexUV vertices[] =
    {
        VertexUV(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(0.0f, 1.0f)),
        VertexUV(Vector3f(-0.5f, 0.5f, 0.5f), Vector2f(0.0f, 0.0f)),
        VertexUV(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(1.0f, 0.0f)),

        VertexUV(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(0.0f, 1.0f)),
        VertexUV(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(1.0f, 0.0f)),
        VertexUV(Vector3f(0.5f, -0.5f, 0.5f), Vector2f(1.0f, 1.0f))
    };

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
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // �տ� position�� float 4���� 12����Ʈ�ϱ� 12.
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

void QuadUV::BindBuffers(ID3D11DeviceContext* deviceContext)
{
    // Bind
    unsigned int stride = sizeof(VertexUV); // �ѹ��� �� ���� ���� ��.
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ���� �׸� ���� LineList.

    transform.Bind(deviceContext);
}