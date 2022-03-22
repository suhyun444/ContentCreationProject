#pragma once
#include "DXApp.h"
#include "InputHandler.h"

class Engine : public DXApp
{
public:
	Engine();
	Engine(HINSTANCE hInstance, int width, int height, std::wstring title);
	~Engine();
	void SetUpVariable(HINSTANCE hInstance, int width, int height, std::wstring title);
	bool Initialize() override;
	int Run() override;

protected:
	void Update() override;
	void DrawScene() override;

private:
	int quadCount = 0;
	int triangleCount = 0;
	bool InitializeScene();

	InputHandler inputHandler;
};

