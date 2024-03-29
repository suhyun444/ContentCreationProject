#include "Mesh.h"

Mesh::Mesh()
    : vertexCount(0), vertexBuffer(0), inputLayout(0),
    transform(),
    position(Vector3f::Zero),
    rotation(Vector3f::Zero),
    scale(Vector3f::One),
    collisionScale(Vector3f::Zero),
    collisionOffset(Vector3f::Zero),
    mass(200),
    tag("default"),
    sortingOrder(1)
{
}
Mesh::Mesh(float _mass)
    : vertexCount(0), vertexBuffer(0), inputLayout(0),
    transform(), 
    position(Vector3f::Zero),
    rotation(Vector3f::Zero),
    scale(Vector3f::One),
    collisionScale(Vector3f::Zero),
    collisionOffset(Vector3f::Zero),
    tag("default")
{
    mass = _mass;
}
Mesh::~Mesh()
{
}
void Mesh::Collide(Mesh* collision)
{

}
std::vector<Vector3f> Mesh::GetVertics()
{
    std::vector<Vector3f> returnVertics;
    int vertexCount = verticsRadians.size();
    Vector3f collisionPosition = position + collisionOffset;
    for (int i = 0; i < vertexCount; i++)
    {
        float radian = verticsRadians[i].first + rotation.z * MathUtil::Deg2Rad;
        Vector3f vertex = Vector3f(cosf(radian), sinf(radian), 0) * verticsRadians[i].second;
        if (collisionScale.x == 0 && collisionScale.y == 0)
        {
            vertex.x *= scale.x;
            vertex.y *= scale.y;

        }
        else
        {
            vertex.x *= collisionScale.x;
            vertex.y *= collisionScale.y;
        }
        vertex += collisionPosition;
        returnVertics.push_back(vertex);
    }
    return returnVertics;
}
void Mesh::SetIsLeft(ID3D11DeviceContext* deviceContext, ID3D11Buffer* unitBuffer)
{
    
}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    meshShader->Bind(deviceContext, curAnimationState);
    BindBuffers(deviceContext);
    DrawBuffers(deviceContext);
}

void Mesh::BindBuffers(ID3D11DeviceContext* deviceContext)
{
    // Bind
    unsigned int stride = sizeof(Vertex); 
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 

    transform.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext)
{
    deviceContext->Draw(vertexCount, 0); 
}

void Mesh::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
    transform.transformMatrix = Matrix4f::Scale(scale) * Matrix4f::Rotation(rotation) * Matrix4f::Translation(position);
}

void Mesh::SetPosition(float x, float y, float z)
{
    position = Vector3f(x, y, z);
}

void Mesh::SetPosition(Vector3f position)
{
    this->position = position;
}

void Mesh::SetRotation(float x, float y, float z)
{
    rotation = Vector3f(x, y, z);
}

void Mesh::SetRotation(Vector3f rotation)
{
    this->rotation = rotation;
}

void Mesh::SetScale(float x, float y, float z)
{
    scale = Vector3f(x, y, z);
}

void Mesh::SetScale(Vector3f scale)
{
    this->scale = scale;
}

void Mesh::SetCollisionScale(float x, float y, float z)
{
    collisionScale = Vector3f(x, y, z);
}
void Mesh::SetCollisionScale(Vector3f scale)
{
    collisionScale = scale;
}
void Mesh::SetCollisionOffset(float x, float y, float z)
{
    collisionOffset = Vector3f(x, y, z);
}
void Mesh::SetCollisionOffset(Vector3f scale)
{
    collisionOffset = scale;
}
void Mesh::SetMass(float mass)
{
    this->mass = mass;
}
void Mesh::SetTag(string tag)
{
    this->tag = tag;
}
void Mesh::SetIsTrigger(bool isTrigger)
{
    this->isTrigger = isTrigger;
}
void Mesh::SetIsEnable(bool isEnable)
{
    this->isEnable = isEnable;
}
void Mesh::SetSoringOrder(int order)
{
    sortingOrder = order;
}