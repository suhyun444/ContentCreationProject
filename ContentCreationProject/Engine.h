#pragma once
#include "DXApp.h"
#include "InputHandler.h"
#include "Camera.h"
#include "MathUtil.h"
#include "Quad.h"
#include "BasicShader.h"
#include "TextureMappingShader.h"
#include "CollisionHandler.h"
#include "MeshHandler.h"
#include "Player.h"
#include "Crab.h"
#include "Timer.h"
#include "Raycast.h"
#include "PuzzleStone.h"

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
	MeshHandler meshHandler;
	Raycast raycast;
	Timer timer;
	Camera camera;

	Player player;
	Crab crab;
	Quad quad;
	PuzzleStone puzzleStone;
	ComPtr<ID3D11Buffer> unitBuffer;
};

