#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	//Engine engine = Engine(hInstance, 800, 800, L"���� ����");
	Engine engine;
	engine.SetUpVariable(hInstance, 800, 800, L"���� ����");
	if (engine.Initialize() == false)
	{
		MessageBox(nullptr, L"���� ����ȭ ����", L"����", 0);
		exit(-1);
	}
	engine.Run();
}