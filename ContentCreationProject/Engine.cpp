#include "Engine.h"
#include <d3dcompiler.h>
#include <iostream>

Engine::Engine() : DXApp()
{

}
Engine::Engine(HINSTANCE hInstance, int width, int height, std::wstring title)
	: DXApp(hInstance, width, height, title)
{

}
void Engine::SetUpVariable(HINSTANCE hInstance, int width, int height, std::wstring title)
{
	Window::SetInstance(hInstance);
	Window::SetWidth(width);
	Window::SetHeight(height);
	Window::SetTitle(title);
}

Engine::~Engine()
{
}

//창, 장치 생성
bool Engine::Initialize()
{
	if (DXApp::Initialize() == false)
	{
		return false;
	}
	if (DXApp::ResizeBackBuffer() == false)
	{
		return false;
	}
	if (InitializeScene() == false)
	{
		return false;
	}
	if (inputHandler.Initialize(Window::Instance(), Window::WindowHandle(), Window::Width(), Window::Height()) == false)
	{
		return false;
	}
	if (timer.Initialize() == false)
	{
		return false;
	}
	return true;
}

//메시지 처리루프 , 엔진 루프
int Engine::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			DrawScene();
		}
	}
	return 0;
}

void Engine::Update()
{
	timer.Frame();
	inputHandler.Frame();
	camera.UpdateCamera();

	int x = (inputHandler.IsKeyPressed(DIK_RIGHTARROW) ? 1 : 0) + (inputHandler.IsKeyPressed(DIK_LEFTARROW) ? -1 : 0);
	player.UpdateVelocity(x);
	if (inputHandler.IsKeyDown(DIK_SPACE))player.Jump();
	if (inputHandler.IsKeyDown(DIK_X))player.Attack();
	player.Update(timer.GetTime());

	collisionHandler.BoardPhase();
	meshHandler.UpdateBuffer(deviceContext.Get());
}

void Engine::DrawScene()
{
	//배경 색
	float backgroundColor[4] = {1.0f,1.0f,1.0f,1.0f };

	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

	camera.BindBuffer(deviceContext.Get());

	meshHandler.RenderBuffer(deviceContext.Get());

#pragma region  player sprite filp logic
	Matrix4f unitInfo;
	if (player.GetIsLeft())unitInfo = Matrix4f::Identity();
	deviceContext->UpdateSubresource(unitBuffer.Get(), NULL, nullptr, &unitInfo, 0, 0);
	deviceContext->VSSetConstantBuffers(2, 1, unitBuffer.GetAddressOf());
#pragma endregion

	swapChain->Present(1, 0);
}

bool Engine::InitializeScene() {
	camera = Camera(
		70.0f * MathUtil::Deg2Rad,
		(float)Window::Width(),
		(float)Window::Height(),
		0.1f,
		100.0f
	);

	//카메라 z위치 조정
	camera.SetPosition(0.0f, 0.0f, -5.0f);
	if (camera.CreateBuffer(device.Get()) == false)
	{
		return false;
	}
	

	D3D11_BUFFER_DESC unitBufferDesc;
	memset(&unitBufferDesc, 0, sizeof(unitBufferDesc));
	unitBufferDesc.ByteWidth = sizeof(Matrix4f) * 2;
	unitBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	unitBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	unitBufferDesc.CPUAccessFlags = 0;
	unitBufferDesc.MiscFlags = 0;

	Matrix4f unitInfo;

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = &unitInfo;

	HRESULT result = device->CreateBuffer(
		&unitBufferDesc,
		&data,
		unitBuffer.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"유닛 버퍼 생성 실패", L"오류", 0);
		throw std::exception("유닛 버퍼 생성 실패");
		return false;
	}


	if (quad.InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad.SetPosition(0.0f, -3.0f, 0.0f);
	quad.SetScale(10.0f, 1.0f, 1.0f);
	quad.SetMass(0);
	collisionHandler.Add(&quad);
	meshHandler.Add(&quad);
	quad.SetTag("Ground");

	std::vector<std::wstring> playerSpriteSheet;
	for (int i = 1; i < 9; i++)playerSpriteSheet.push_back(L"PlayerIdle" + to_wstring(i) + L".png");
	for (int i = 1; i < 11; i++)playerSpriteSheet.push_back(L"PlayerWalk" + to_wstring(i) + L".png");
	for (int i = 1; i < 19; i++)playerSpriteSheet.push_back(L"PlayerAttack" + to_wstring(i) + L".png");
	if (player.InitializeBuffers(device.Get(), playerSpriteSheet) == false)
	{
		return false;
	}
	player.SetPosition(0.0f, -1.0f, 0.0f);
	player.SetScale(1.5f, 1.5f, 1.0f);
	player.SetRotation(0.0f, 0.0f, 0.0f);
	player.SetCollisionScale(0.6f, 1.5f, 0.0f);
	collisionHandler.Add(&player);
	meshHandler.Add(&player);

	if (player.groundChecker.InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	//player.groundChecker.InitializeCollideCallback(std::bind(&Player::GroundCheck, &player));
	player.groundChecker.SetScale(0.0f, 0.0f, 0.0f);
	player.groundChecker.SetCollisionScale(0.3f, 0.001f, 0.0f);
	collisionHandler.Add(&player.groundChecker);
	meshHandler.Add(&player.groundChecker);

	return true;
}