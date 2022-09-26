#include "Engine.h"
#include <d3dcompiler.h>
#include <iostream>

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

//창, 장치 생성
bool Engine::Initialize()
{
	if (DXApp::Initialize() == false)
	{
		return false;
	}
	if (DXApp::ResizeBackBuffer() == false)
	{
		return false;
	}
	if (InitializeScene() == false)
	{
		return false;
	}
	if (inputHandler.Initialize(Window::Instance(), Window::WindowHandle(), Window::Width(), Window::Height()) == false)
	{
		return false;
	}
	if (timer.Initialize() == false)
	{
		return false;
	}
	return true;
}

//메시지 처리루프 , 엔진 루프
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
	timer.Frame();
	inputHandler.Frame();
	for (int i = 0; i < 8; i++)if (crab[i].IsEnable())crab[i].Update(timer.GetTime());
	for (int i = 0; i < 6; i++)puzzleStone[i].Update(timer.GetTime());

	int x = (inputHandler.IsKeyPressed(DIK_RIGHTARROW) ? 1 : 0) + (inputHandler.IsKeyPressed(DIK_LEFTARROW) ? -1 : 0);
	player.UpdateVelocity(x, timer.GetTime());
	if (inputHandler.IsKeyDown(DIK_SPACE))player.Jump();
	if (inputHandler.IsKeyDown(DIK_X))player.Attack();
	player.Update(timer.GetTime());
	backGround.SetPosition(camera.Position().x, camera.Position().y - 0.2f, 0.0f);

	collisionHandler.BoardPhase();
	meshHandler.UpdateBuffer(deviceContext.Get());
	camera.UpdateCamera();
}

void Engine::DrawScene()
{
	//배경 색
	float backgroundColor[4] = { 1.0f,1.0f,1.0f,1.0f };

	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

	camera.BindBuffer(deviceContext.Get());


	meshHandler.RenderBuffer(deviceContext.Get(), unitBuffer.Get(),  !player.IsEnable());

	swapChain->Present(1, 0);
}

bool Engine::InitializeScene() {
	camera = Camera(
		70.0f * MathUtil::Deg2Rad,
		(float)Window::Width(),
		(float)Window::Height(),
		0.1f,
		100.0f
	);

	//카메라 z위치 조정
	camera.SetPosition(0.0f, 0.0f, -5.0f);
	if (camera.CreateBuffer(device.Get()) == false)
	{
		return false;
	}


	D3D11_BUFFER_DESC unitBufferDesc;
	memset(&unitBufferDesc, 0, sizeof(unitBufferDesc));
	unitBufferDesc.ByteWidth = sizeof(Matrix4f) * 2;
	unitBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	unitBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	unitBufferDesc.CPUAccessFlags = 0;
	unitBufferDesc.MiscFlags = 0;

	Matrix4f unitInfo;

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = &unitInfo;

	HRESULT result = device->CreateBuffer(
		&unitBufferDesc,
		&data,
		unitBuffer.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"유닛 버퍼 생성 실패", L"오류", 0);
		throw std::exception("유닛 버퍼 생성 실패");
		return false;
	}

	raycast.Initialize();
	raycast.collisionHandler = &collisionHandler;

#pragma region  InitMap


	std::vector<std::wstring> BackGroundSpriteSheet;
	BackGroundSpriteSheet.push_back(L"BackGround.png");
	if (backGround.InitializeBuffers(device.Get(), BackGroundSpriteSheet) == false)
	{
		return false;
	}
	backGround.SetAnimationState("BackGround.png");
	backGround.SetScale(16, 9, 1.0f);
	meshHandler.Add(&backGround);

	if (quad[0].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[0].SetPosition(0.0f, -5.0f, 0.0f);
	quad[0].SetScale(10.0f, 5.0f, 1.0f);
	quad[0].SetMass(0);
	collisionHandler.Add(&quad[0]);
	meshHandler.Add(&quad[0]);
	quad[0].SetTag("Ground");

	if (quad[1].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[1].SetPosition(7.0f, -5.0f, 0.0f);
	quad[1].SetScale(4.0f, 9.0f, 1.0f);
	quad[1].SetMass(0);
	collisionHandler.Add(&quad[1]);
	meshHandler.Add(&quad[1]);
	quad[1].SetTag("Ground");

	if (quad[2].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[2].SetPosition(3.3f, -1.5f, 0.0f);
	quad[2].SetScale(2.0f, 0.3f, 1.0f);
	quad[2].SetMass(0);
	collisionHandler.Add(&quad[2]);
	meshHandler.Add(&quad[2]);
	quad[2].SetIsEnable(false);
	quad[2].SetTag("Ground");

	if (quad[3].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[3].SetPosition(19.0f, -7.0f, 0.0f);
	quad[3].SetScale(20.0f, 5.0f, 1.0f);
	quad[3].SetMass(0);
	collisionHandler.Add(&quad[3]);
	meshHandler.Add(&quad[3]);
	quad[3].SetTag("Ground");

	if (quad[4].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[4].SetPosition(11.0f, -3.5f, 0.0f);
	quad[4].SetScale(2.0f, 0.3f, 1.0f);
	quad[4].SetMass(0);
	collisionHandler.Add(&quad[4]);
	meshHandler.Add(&quad[4]);
	quad[4].SetIsEnable(false);
	quad[4].SetTag("Ground");

	if (quad[5].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[5].SetPosition(13.8f, -2.3f, 0.0f);
	quad[5].SetScale(2.0f, 0.3f, 1.0f);
	quad[5].SetMass(0);
	collisionHandler.Add(&quad[5]);
	meshHandler.Add(&quad[5]);
	quad[5].SetIsEnable(false);
	quad[5].SetTag("Ground");

	if (quad[6].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[6].SetPosition(11.0f, -1.1f, 0.0f);
	quad[6].SetScale(2.0f, 0.3f, 1.0f);
	quad[6].SetMass(0);
	collisionHandler.Add(&quad[6]);
	meshHandler.Add(&quad[6]);
	quad[6].SetIsEnable(false);
	quad[6].SetTag("Ground");

	if (quad[7].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[7].SetPosition(-15.0f, 4.0f, 0.0f);
	quad[7].SetScale(20.0f, 20.0f, 1.0f);
	quad[7].SetMass(0);
	collisionHandler.Add(&quad[7]);
	meshHandler.Add(&quad[7]);
	quad[7].SetTag("Ground");

	if (quad[8].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[8].SetPosition(39.0f, 4.0f, 0.0f);
	quad[8].SetScale(20.0f, 20.0f, 1.0f);
	quad[8].SetMass(0);
	collisionHandler.Add(&quad[8]);
	meshHandler.Add(&quad[8]);
	quad[8].SetTag("Ground");

	if (quad[9].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[9].SetPosition(23.0f, -3.5f, 0.0f);
	quad[9].SetScale(1.0f, 0.3f, 1.0f);
	quad[9].SetMass(0);
	collisionHandler.Add(&quad[9]);
	meshHandler.Add(&quad[9]);
	quad[9].SetIsEnable(false);
	quad[9].SetTag("Ground");

	if (quad[10].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[10].SetPosition(24.65f, -3.5f, 0.0f);
	quad[10].SetScale(0.3f, 2.0f, 1.0f);
	quad[10].SetMass(0);
	collisionHandler.Add(&quad[10]);
	meshHandler.Add(&quad[10]);
	quad[10].SetTag("Ground");

	if (quad[11].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[11].SetPosition(27.0f, -3.5f, 0.0f);
	quad[11].SetScale(0.3f, 2.0f, 1.0f);
	quad[11].SetMass(0);
	collisionHandler.Add(&quad[11]);
	meshHandler.Add(&quad[11]);
	quad[11].SetTag("Ground");
	//quad[11].SetIsEnable(false);
	if (quad[12].InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	quad[12].SetPosition(27.5f, -2.35f, 0.0f);
	quad[12].SetScale(6.0f, 0.3f, 1.0f);
	quad[12].SetMass(0);
	collisionHandler.Add(&quad[12]);
	meshHandler.Add(&quad[12]);
	quad[12].SetTag("Ground");

	std::vector<std::wstring>SandSpriteSheet;
	for (int i = 1; i < 4; i++)SandSpriteSheet.push_back(L"Sand" + to_wstring(i) + L".png");
	for (int i = 0; i < 20; i++)
	{
		if (platformsA[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsA[i].SetPosition(-4.75f + i * 0.5f, -2.55f, 0.0f);
		meshHandler.Add(&platformsA[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		if (platformsB[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsB[i].SetPosition(2.55f + i * 0.5f, -1.4f, 0.0f);
		meshHandler.Add(&platformsB[i]);
		platformsB[i].SetIsEnable(false);
	}
	for (int i = 0; i < 8; i++)
	{
		if (platformsC[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsC[i].SetPosition(5.25f + i * 0.5f, -0.55f, 0.0f);
		meshHandler.Add(&platformsC[i]);
	}
	for (int i = 0; i < 40; i++)
	{
		if (platformsD[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsD[i].SetPosition(9.25f + i * 0.5f, -4.55f, 0.0f);
		meshHandler.Add(&platformsD[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		if (platformsE[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsE[i].SetPosition(10.25f + i * 0.5f, -1.0f, 0.0f);
		meshHandler.Add(&platformsE[i]);
		platformsE[i].SetIsEnable(false);
	}
	for (int i = 0; i < 4; i++)
	{
		if (platformsF[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsF[i].SetPosition(13.05f + i * 0.5f, -2.2f, 0.0f);
		meshHandler.Add(&platformsF[i]);
		platformsF[i].SetIsEnable(false);
	}
	for (int i = 0; i < 4; i++)
	{
		if (platformsG[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsG[i].SetPosition(10.25f + i * 0.5f, -3.4f, 0.0f);
		meshHandler.Add(&platformsG[i]);
		platformsG[i].SetIsEnable(false);
	}
	for (int i = 0; i < 2; i++)
	{
		if (platformsH[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsH[i].SetPosition(22.75f + i * 0.5f, -3.4f, 0.0f);
		meshHandler.Add(&platformsH[i]);
		platformsH[i].SetIsEnable(false);
	}
	for (int i = 0; i < 9; i++)
	{
		if (platformsI[i].InitializeBuffers(device.Get(), SandSpriteSheet) == false)
		{
			return false;
		}
		platformsI[i].SetPosition(24.75f + i * 0.5f, -2.25f, 0.0f);
		meshHandler.Add(&platformsI[i]);
	}



	std::vector<std::wstring> playerSpriteSheet;
	for (int i = 1; i < 9; i++)playerSpriteSheet.push_back(L"PlayerIdle" + to_wstring(i) + L".png");
	for (int i = 1; i < 11; i++)playerSpriteSheet.push_back(L"PlayerWalk" + to_wstring(i) + L".png");
	for (int i = 1; i < 19; i++)playerSpriteSheet.push_back(L"PlayerAttack" + to_wstring(i) + L".png");
	if (player.InitializeBuffers(device.Get(), playerSpriteSheet) == false)
	{
		return false;
	}
	player.camera = &camera;
	collisionHandler.Add(&player);
	meshHandler.Add(&player);

	if (player.groundChecker.InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	collisionHandler.Add(&player.groundChecker);

	if (player.headChecker.InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	collisionHandler.Add(&player.headChecker);

	if (player.hitbox.InitializeBuffers(device.Get()) == false)
	{
		return false;
	}
	collisionHandler.Add(&player.hitbox);

	std::vector<std::wstring> playerHeartSpriteSheet;
	playerHeartSpriteSheet.push_back(L"PlayerHeart.png");
	for (int i = 0; i < 3; i++)
	{
		if (player.heart[i].InitializeBuffers(device.Get(), playerHeartSpriteSheet) == false)
		{
			return false;
		}
		meshHandler.Add(&player.heart[i]);
	}



	std::vector<std::wstring> crabSpriteSheet;
	for (int i = 1; i < 6; i++)crabSpriteSheet.push_back(L"CrabIdle" + to_wstring(i) + L".png");
	for (int i = 1; i < 10; i++)crabSpriteSheet.push_back(L"CrabWalk" + to_wstring(i) + L".png");
	for (int i = 1; i < 13; i++)crabSpriteSheet.push_back(L"CrabAttack" + to_wstring(i) + L".png");
	for (int i = 1; i < 19; i++)crabSpriteSheet.push_back(L"CrabDead" + to_wstring(i) + L".png");
	Vector3f crabPositions[8] = { Vector3f(1.5f, -2.0f, 0.0f), Vector3f(-0.5f, -2.0f, 0.0f), Vector3f(12.0f,-4.0f,0.0f), Vector3f(16.0f,-4.0f,0.0f) ,
								Vector3f(18.0f,-4.0f,0.0f) ,Vector3f(20.0f,-4.0f,0.0f), Vector3f(22.0f,-4.0f,0.0f), Vector3f(27.0f, -1.70f, 0.0f) };
	for (int i = 0; i < 8; i++)
	{
		if (crab[i].InitializeBuffers(device.Get(), crabSpriteSheet) == false)
		{
			return false;
		}
		crab[i].SetPlayer(&player);
		collisionHandler.Add(&crab[i]);
		meshHandler.Add(&crab[i]);
		crab[i].SetPosition(crabPositions[i]);

		if (crab[i].hitbox.InitializeBuffers(device.Get()) == false)
		{
			return false;
		}
		collisionHandler.Add(&crab[i].hitbox);
	}



	std::vector<std::wstring> puzzleStoneSpriteSheet;
	for (int i = 1; i < 12; i++)puzzleStoneSpriteSheet.push_back(L"PuzzleStone" + to_wstring(i) + L".png");
	if (puzzleStone[0].InitializeBuffers(device.Get(), puzzleStoneSpriteSheet) == false)
	{
		return false;
	}
	puzzleStone[0].SetPosition(3.0f, -2.05f, 0.0f);
	puzzleStone[0].walls.push_back(&quad[2]);
	for (int i = 0; i < 4; i++)puzzleStone[0].walls.push_back(&platformsB[i]);
	collisionHandler.Add(&puzzleStone[0]);
	meshHandler.Add(&puzzleStone[0]);

	if (puzzleStone[1].InitializeBuffers(device.Get(), puzzleStoneSpriteSheet) == false)
	{
		return false;
	}
	puzzleStone[1].SetPosition(14.0f, -4.0f, 0.0f);
	puzzleStone[1].walls.push_back(&quad[4]);
	puzzleStone[1].walls.push_back(&puzzleStone[2]);
	for (int i = 0; i < 4; i++)puzzleStone[1].walls.push_back(&platformsG[i]);
	collisionHandler.Add(&puzzleStone[1]);
	meshHandler.Add(&puzzleStone[1]);

	if (puzzleStone[2].InitializeBuffers(device.Get(), puzzleStoneSpriteSheet) == false)
	{
		return false;
	}
	puzzleStone[2].SetPosition(10.4f, -2.85f, 0.0f);
	puzzleStone[2].walls.push_back(&quad[5]);
	puzzleStone[2].walls.push_back(&puzzleStone[3]);
	for (int i = 0; i < 4; i++)puzzleStone[2].walls.push_back(&platformsF[i]);
	collisionHandler.Add(&puzzleStone[2]);
	meshHandler.Add(&puzzleStone[2]);
	puzzleStone[2].SetIsEnable(false);

	if (puzzleStone[3].InitializeBuffers(device.Get(), puzzleStoneSpriteSheet) == false)
	{
		return false;
	}
	puzzleStone[3].SetPosition(14.4f, -1.65f, 0.0f);
	puzzleStone[3].walls.push_back(&quad[6]);
	for (int i = 0; i < 4; i++)puzzleStone[3].walls.push_back(&platformsE[i]);
	collisionHandler.Add(&puzzleStone[3]);
	meshHandler.Add(&puzzleStone[3]);
	puzzleStone[3].SetIsEnable(false);

	if (puzzleStone[4].InitializeBuffers(device.Get(), puzzleStoneSpriteSheet) == false)
	{
		return false;
	}
	puzzleStone[4].SetPosition(22.0f, -4.0f, 0.0f);
	puzzleStone[4].walls.push_back(&quad[9]);
	puzzleStone[4].walls.push_back(&quad[11]);
	for (int i = 0; i < 2; i++)puzzleStone[4].walls.push_back(&platformsH[i]);
	collisionHandler.Add(&puzzleStone[4]);
	meshHandler.Add(&puzzleStone[4]);

	if (puzzleStone[5].InitializeBuffers(device.Get(), puzzleStoneSpriteSheet) == false)
	{
		return false;
	}
	puzzleStone[5].SetPosition(26.4f, -1.70f, 0.0f);
	puzzleStone[5].walls.push_back(&quad[10]);
	puzzleStone[5].walls.push_back(&quad[11]);
	collisionHandler.Add(&puzzleStone[5]);
	meshHandler.Add(&puzzleStone[5]);

	std::vector<std::wstring> doorSpriteSheet;
	doorSpriteSheet.push_back(L"Door.png");
	if (door.InitializeBuffers(device.Get(), doorSpriteSheet) == false)
	{
		return false;
	}
	door.SetPosition(28.3f, -4.15f, 0.0f);
	door.SetScale(0.7f, 0.7f, 1.0f);
	door.SetAnimationState("Door.png");
	door.SetTag("Door");
	collisionHandler.Add(&door);
	meshHandler.Add(&door);

	std::vector<std::wstring> clearSpriteSheet;
	clearSpriteSheet.push_back(L"Clear.png");
	if (clear.InitializeBuffers(device.Get(), clearSpriteSheet) == false)
	{
		return false;
	}
	clear .SetPosition(0, 0, 0.0f);
	clear.SetScale(13, 8, 1.0f);
	clear.SetAnimationState("Clear.png");
	meshHandler.Add(&clear);
	clear.SetIsEnable(false);

	std::vector<std::wstring> gameoverSpirteSheet;
	gameoverSpirteSheet.push_back(L"GameOver.png");
	if (dead.InitializeBuffers(device.Get(), gameoverSpirteSheet) == false)
	{
		return false;
	}
	dead.SetPosition(0, 0, 0.0f);
	dead.SetScale(13, 8, 1);
	dead.SetAnimationState("GameOver.png");
	meshHandler.Add(&dead);
	dead.SetIsEnable(false);
	player.clear = &clear;
	player.gameOver = &dead;
#pragma endregion


	return true;
}