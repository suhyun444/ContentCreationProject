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
#include "Platform.h"

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
	Quad quad[9];
	Platform platformsA[20];
	Platform platformsB[4];
	Platform platformsC[10];
	Platform platformsD[40];
	Platform platformsE[4];
	Platform platformsF[4];
	Platform platformsG[4];
	PuzzleStone puzzleStone[4];
	QuadUV backGround;
	ComPtr<ID3D11Buffer> unitBuffer;
};

