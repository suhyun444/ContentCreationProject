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
	if (InitializeScene() == false)
	{
		return false;
	}
	if (inputHandler.Initialize(Window::Instance(), Window::WindowHandle(), Window::Width(), Window::Height()) == false)
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
	inputHandler.Frame();
}

void Engine::DrawScene()
{
	//배경 색
	float backgroundColor[4] = { 0.1f,0.5f,0.1f,1.0f };

	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

	//camera.BindBuffer(deviceContext.Get());

	////그리기 Bind + Render
	//BasicShader::BindVertexShader(deviceContext.Get());

	////그리기
	//BasicShader::BindWhiteShader(deviceContext.Get());
	//mouseCursor.RenderBuffers(deviceContext.Get());
	//meshHandler.RenderMeshs(deviceContext.Get());

	////색깔 그리기
	//BasicShader::BindColorShader(deviceContext.Get());

	//FrontBuffer <-> BackBuffer 바꾸기
	swapChain->Present(1, 0);
}

bool Engine::InitializeScene() {
	/*camera = Camera(
		70.0f * MathUtil::Deg2Rad,
		(float)Window::Width(),
		(float)Window::Height(),
		0.1f,
		100.0f
	);*/

	//카메라 z위치 조정
	//camera.SetPosition(0.0f, 0.0f, -20);

	//if (camera.CreateBuffer(device.Get()) == false)
	//{
	//	return false;
	//}
	//if (BasicShader::Compile(device.Get()) == false)
	//{
	//	return false;
	//}
	//if (BasicShader::Create(device.Get()) == false)
	//{
	//	return false;
	//}

	return true;
}