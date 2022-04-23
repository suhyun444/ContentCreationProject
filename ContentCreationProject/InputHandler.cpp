#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{

}
InputHandler::~InputHandler()
{

}

bool InputHandler::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	HRESULT result = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)directInput.GetAddressOf(),
		NULL
	);
	if (FAILED(result))
	{
		return false;
	}

	result = directInput.Get()->CreateDevice(
		GUID_SysKeyboard,
		keyboard.GetAddressOf(),
		NULL
	);
	if (FAILED(result))
	{
		return false;
	}

	result = keyboard.Get()->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	result = keyboard.Get()->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = keyboard.Get()->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	result = directInput.Get()->CreateDevice(
		GUID_SysMouse,
		mouse.GetAddressOf(),
		NULL
	);
	if (FAILED(result))
	{
		return false;
	}

	result = mouse.Get()->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	result = mouse.Get()->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}
	ShowCursor(true);
	result = mouse.Get()->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool InputHandler::Frame()
{
	bool result;

	result = ReadKeyBoard();
	if (!result)
	{
		return false;
	}

	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	ProcessInput();

	return true;
}

bool InputHandler::ReadKeyBoard()
{
	HRESULT result;

	result = keyboard.Get()->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard.Get()->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool InputHandler::ReadMouse()
{
	HRESULT result;

	result = mouse.Get()->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mouse.Get()->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}
void InputHandler::ProcessInput()
{
	mouseX += mouseState.lX;
	mouseY += mouseState.lY;

	screenX = min(screenWidth, mouseX);
	screenY = min(screenHeight, mouseY);
	screenX = max(0, mouseX);
	screenY = max(0, mouseY);
	return;
}
bool InputHandler::IsKeyPressed(int state)
{
	if (keyboardState[state] & 0x80)
	{
		return true;
	}
	return false;
}
bool InputHandler::IsKeyDown(int state)
{
	//state == 	DIK_"keycode"
	if (keyboardIsPressed[state] && keyboardState[state] & 0x80)
	{
		return false;
	}
	if (keyboardState[state] & 0x80)
	{
		keyboardIsPressed[state] = true;
		return true;
	}
	keyboardIsPressed[state] = (keyboardState[state] & 0x80);
	return false;
}
bool InputHandler::IsMouseButtonDown(int index)
{
	if (mouseButtonIsPressed[index] && mouseState.rgbButtons[index] & 0x80)
	{
		return false;
	}
	if (mouseState.rgbButtons[index] & 0x80)
	{
		//Point mousePosition = GetMouseLocation();
		//startPosition = Vector2f(mousePosition.x, -mousePosition.y) / 800.0f;
		mouseButtonIsPressed[index] = true;
		return true;
	}
	return false;
}
bool InputHandler::IsMouseButtonPressed(int index)
{
	if (mouseState.rgbButtons[index] & 0x80)
	{
		return true;
	}
	return false;
}
bool InputHandler::IsMouseButtonUp(int index)
{
	if (mouseButtonIsPressed[index] && !(mouseState.rgbButtons[index] & 0x80))
	{
		//Point mousePosition = GetMouseLocation();
		//endPosition = Vector2f(mousePosition.x, -mousePosition.y) / 800.0f;
		mouseButtonIsPressed[index] = false;
		return true;
	}
	return false;
}
