#include "Engine.h"
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	//Engine engine = Engine(hInstance, 800, 800, L"������ ���� �ǹ� ������");
	Engine engine;
	engine.SetUpVariable(hInstance, 1280, 720, L"������ ���� �ǹ� ������");
	if (engine.Initialize() == false)
	{
		MessageBox(nullptr, L"���� ����ȭ ����", L"����", 0);
		exit(-1);
	}
	engine.Run();
}