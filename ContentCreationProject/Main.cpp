#include "Engine.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"DirectXTex.lib")
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	//Engine engine = Engine(hInstance, 800, 800, L"������ ���� �ǹ� ������");
	Engine engine;
	engine.SetUpVariable(hInstance, 1280, 720, L"������ ���� �ǹ� ������");
	if (engine.Initialize() == false)
	{
		MessageBox(nullptr, L"���� �ʱ�ȭ ����", L"����", 0);
		exit(-1);
	}
	engine.Run();
}