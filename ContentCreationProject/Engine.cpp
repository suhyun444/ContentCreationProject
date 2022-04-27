#include "Engine.h"
#include <d3dcompiler.h>

//마우스 포인터 실위치와 윈도우 위치를 다르게하면 마우스 고정없이 마우스 포인터를 쓸 수 있지않을까?
//범위 밖으로 넘어갔을때 윈도우위치에맞게 Clamp해주고 "다시 들어왔을때" 마우스 포인터 코드 위치가 바뀌도록
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

	if (player.InitializeBuffers(device.Get(), L"Player.png") == false)
	{
		return false;
	}
	player.SetPosition(0.0f, -1.0f, 0.0f);
	player.SetScale(1.0f, 1.0f, 1.0f);
	player.SetCollisionScale(0.2f, 0.85f, 0.0f);
	collisionHandler.Add(&player);
	meshHandler.Add(&player);

	if (player.groundChecker.InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	player.groundChecker.InitializeCollideCallback(std::bind(&Player::GroundCheck, &player));
	player.groundChecker.SetScale(0.0f, 0.0f, 0.0f);
	player.groundChecker.SetCollisionScale(0.3f, 0.001f, 0.0f);
	collisionHandler.Add(&player.groundChecker);
	meshHandler.Add(&player.groundChecker);

	return true;
}