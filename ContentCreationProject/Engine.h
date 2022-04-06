#pragma once
#include "DXApp.h"
#include "InputHandler.h"
#include "Camera.h"
#include "MathUtil.h"
#include "Quad.h"
#include "QuadUV.h"
#include "BasicShader.h"
#include "TextureMappingShader.h"
#include "CollisionHandler.h"

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
	CollisionHandler collisionHandler;

	Camera camera;
	Quad quad;
	QuadUV quadUV;
};

