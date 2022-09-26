#include "Engine.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"DirectXTex.lib")
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	//Engine engine = Engine(hInstance, 800, 800, L"能刨明 力累 角公 牧刨明");
	Engine engine;
	engine.SetUpVariable(hInstance, 1280, 720, L"能刨明 力累 角公 牧刨明");
	if (engine.Initialize() == false)
	{
		MessageBox(nullptr, L"浚柳 檬扁拳 角菩", L"坷幅", 0);
		exit(-1);
	}
	engine.Run();
}