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
	if (InitializeScene() == false)
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

}

void Engine::DrawScene()
{
	//��� ��
	float backgroundColor[4] = { 0.1f,0.5f,0.1f,1.0f };

	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

	//camera.BindBuffer(deviceContext.Get());

	////�׸��� Bind + Render
	//BasicShader::BindVertexShader(deviceContext.Get());

	////�׸���
	//BasicShader::BindWhiteShader(deviceContext.Get());
	//mouseCursor.RenderBuffers(deviceContext.Get());
	//meshHandler.RenderMeshs(deviceContext.Get());

	////���� �׸���
	//BasicShader::BindColorShader(deviceContext.Get());

	//FrontBuffer <-> BackBuffer �ٲٱ�
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

	//ī�޶� z��ġ ����
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