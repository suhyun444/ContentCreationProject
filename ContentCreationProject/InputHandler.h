#pragma once
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <initguid.h>
#include <Windows.h>
#include <wrl.h>
#include <dinput.h>


using Microsoft::WRL::ComPtr;
class InputHandler
{
private:
	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	ComPtr<IDirectInputDevice8> mouse;

	bool keyboardIsPressed[256] = { false, };
	unsigned char keyboardState[256] = { 0, };
	bool mouseButtonIsPressed[4] = { false };
	DIMOUSESTATE mouseState;

	int screenWidth = 0;
	int screenHeight = 0;

	float mouseX = 0.0f;
	float mouseY = 0.0f;
	float screenX = 0.0f;
	float screenY = 0.0f;
private:
	bool ReadKeyBoard();
	bool ReadMouse();
	void ProcessInput();
public:
	InputHandler();
	~InputHandler();

	bool Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight);
	bool Frame();

	bool IsMouseButtonDown(int index);
	bool IsMouseButtonPressed(int index);
	bool IsMouseButtonUp(int index);
	bool IsKeyPressed(int state);
	bool IsKeyDown(int state);
};

