#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	//Engine engine = Engine(hInstance, 800, 800, L"물리 엔진");
	Engine engine;
	engine.SetUpVariable(hInstance, 800, 800, L"물리 엔진");
	if (engine.Initialize() == false)
	{
		MessageBox(nullptr, L"엔진 포기화 실패", L"오류", 0);
		exit(-1);
	}
	engine.Run();
}