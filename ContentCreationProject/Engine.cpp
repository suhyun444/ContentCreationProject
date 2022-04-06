#include "Engine.h"
#include <d3dcompiler.h>

//���콺 ������ ����ġ�� ������ ��ġ�� �ٸ����ϸ� ���콺 �������� ���콺 �����͸� �� �� ����������?
//���� ������ �Ѿ���� ��������ġ���°� Clamp���ְ� "�ٽ� ��������" ���콺 ������ �ڵ� ��ġ�� �ٲ��
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

//â, ��ġ ����
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
	return true;
}

//�޽��� ó������ , ���� ����
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
	camera.UpdateCamera();

	quad.UpdateBuffers(deviceContext.Get());
	quadUV.UpdateBuffers(deviceContext.Get());
	collisionHandler.BoardPhase();

	if (inputHandler.IsKeyPressed(DIK_D))
	{
		quad.SetPosition(Vector3f(quad.Position().x + 0.1f, quad.Position().y, 0.0f));
	}
	if (inputHandler.IsKeyPressed(DIK_A))
	{
		quad.SetPosition(Vector3f(quad.Position().x - 0.1f, quad.Position().y, 0.0f));
	}
	if (inputHandler.IsKeyPressed(DIK_W))
	{
		quad.SetPosition(Vector3f(quad.Position().x, quad.Position().y + 0.1f, 0.0f));
	}
	if (inputHandler.IsKeyPressed(DIK_S))
	{
		quad.SetPosition(Vector3f(quad.Position().x, quad.Position().y - 0.1f, 0.0f));
	}

}

void Engine::DrawScene()
{
	//��� ��
	float backgroundColor[4] = {1.0f,1.0f,1.0f,1.0f };

	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

	camera.BindBuffer(deviceContext.Get());

	BasicShader::Bind(deviceContext.Get());
	quad.RenderBuffers(deviceContext.Get());

	TextureMappingShader::Bind(deviceContext.Get());
	quadUV.RenderBuffers(deviceContext.Get());

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

	//ī�޶� z��ġ ����
	camera.SetPosition(0.0f, 0.0f, -5.0f);
	if (camera.CreateBuffer(device.Get()) == false)
	{
		return false;
	}
	if (BasicShader::Compile(device.Get()) == false)
	{
		return false;
	}
	if (BasicShader::Create(device.Get()) == false)
	{
		return false;
	}
	if (TextureMappingShader::Compile(device.Get(), L"player.png") == false)
	{
		return false;
	}
	if (TextureMappingShader::Create(device.Get()) == false)
	{
		return false;
	}    
	
	if (quad.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer()) == false)
	{
		return false;
	}
	quad.SetPosition(3.0f, 0.0f, 0.0f);
	quad.SetScale(1.0f, 1.0f, 1.0f);
	collisionHandler.Add(&quad);

	if (quadUV.InitializeBuffers(device.Get(), TextureMappingShader::ShaderBuffer()) == false)
	{
		return false;
	}
	quadUV.SetPosition(0.0f, 0.0f, 0.0f);
	quadUV.SetScale(1.0f, 1.0f, 1.0f);
	quadUV.SetCollisionScale(0.2f, 1.0f, 0.0f);
	collisionHandler.Add(&quadUV);

	return true;
}