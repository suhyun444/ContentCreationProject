#include "DXApp.h"

DXApp::DXApp()
{

}
DXApp::DXApp(HINSTANCE hInstance, int width, int height, std::wstring title)
{
	Window::SetInstance(hInstance);
	Window::SetWidth(width);
	Window::SetHeight(height);
	Window::SetTitle(title);
}

DXApp::~DXApp()
{

}

bool DXApp::Initialize()
{
	if (Window::InitializeWindow() == false)
	{
		return false;
	}
	if (InitializeDirect3D() == false)
	{
		return false;
	}
	return true;
}

bool DXApp::InitializeDirect3D()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = Window::WindowHandle();
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = Window::Width();
	swapChainDesc.BufferDesc.Height = Window::Height();

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		swapChain.GetAddressOf(),
		device.GetAddressOf(),
		NULL,
		deviceContext.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"장치 생성 실패", L"오류", 0);
		return false;
	}

	ID3D11Texture2D* backbufferTexture;
	result = swapChain.Get()->GetBuffer(
		NULL,
		__uuidof(ID3D11Texture2D),
		(void**)(&backbufferTexture)
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"백버퍼 정보 얻어오는데 실패", L"오류", 0);
		return false;
	}

	result = device.Get()->CreateRenderTargetView(
		backbufferTexture,
		nullptr,
		renderTargetView.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"렌더 타겟 뷰 생성 실패", L"오류", 0);
		return false;
	}

	backbufferTexture->Release();
	deviceContext.Get()->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
	deviceContext.Get()->OMSetDepthStencilState(nullptr, 1);

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)Window::Width();
	viewport.Height = (float)Window::Height();

	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	deviceContext.Get()->RSSetViewports(1, &viewport);
	return true;
}