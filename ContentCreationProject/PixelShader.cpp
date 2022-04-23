#include <d3dcompiler.h>

#include "PixelShader.h"
#include <iostream>

PixelShader::PixelShader()
    : Shader()
{
}

PixelShader::PixelShader(std::wstring filename)
    : Shader(filename)
{
    profile = "ps_5_0";
}

PixelShader::PixelShader(std::wstring filename, std::string entry, std::string profile)
    : Shader(filename, entry, profile), pixelShader(0)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::Compile(ID3D11Device* device)
{
    // PS ������
    HRESULT result = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        entry.c_str(),
        profile.c_str(),
        NULL,
        NULL,
        shaderBuffer.GetAddressOf(),
        NULL
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�ȼ� ���̴� ������ ����", L"����", 0);
        return false;
    }

    return true;
}

bool PixelShader::Create(ID3D11Device* device)
{
    // PS ����.
    HRESULT result = device->CreatePixelShader(
        shaderBuffer->GetBufferPointer(), // ���� ���� �ּ�.
        shaderBuffer->GetBufferSize(), // �󸶸�ŭ ���� ��.
        nullptr,
        pixelShader.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�ȼ� ���̴� ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void PixelShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetShader(pixelShader.Get(), NULL, NULL);
}

bool PixelShader::CreateSamplerState(ID3D11Device* device)
{
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // ���÷� ������Ʈ ����.
    HRESULT result = device->CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���÷� ������Ʈ ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void PixelShader::BindSamplerState(ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

bool PixelShader::LoadTexture(ID3D11Device* device, std::wstring filename)
{
    Texture texture;
    texture.filename = filename;
    if (texture.LoadTextureFromFile(device) == false)
    {
        return false;
    }
    std::string frameName;
    frameName.assign(filename.begin(), filename.end());
    textures.insert(std::make_pair(frameName,texture));

    return true;
}

void PixelShader::BindTextures(ID3D11DeviceContext* deviceContext, std::string frameName)
{
    auto iter = textures.find(frameName);
    if (iter == textures.end())
        return;

    deviceContext->PSSetShaderResources(
        0,
        1,
        textures[frameName].textureResource.GetAddressOf()
    );
}