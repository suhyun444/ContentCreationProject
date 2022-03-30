#pragma once
#include "Window.h"
#include <d3d11.h>
#include <wrl.h>


using Microsoft::WRL::ComPtr;

class DXApp
{
public:
	DXApp();
	DXApp(HINSTANCE hInstance, int width, int height, std::wstring title);
	virtual ~DXApp();
	virtual bool Initialize();

	virtual int Run() = 0;

protected:
	virtual void Update() = 0;
	virtual void DrawScene() = 0;

	bool InitializeDirect3D();

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11BlendState> blendState;

	D3D11_VIEWPORT viewport;
};



