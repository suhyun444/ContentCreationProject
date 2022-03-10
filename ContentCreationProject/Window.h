#pragma once
#include <Windows.h>
#include <string>
#include <d3d11.h>

class Window
{
private:
	static int width;
	static int height;
	static std::wstring title;
	static HWND hwnd;
	static HINSTANCE hInstance;
public:
	static bool InitializeWindow();
	static bool InitializeWindow(HINSTANCE hInstance, int width, int height, std::wstring title);

	static HWND WindowHandle() { return hwnd; }

	static HINSTANCE Instance() { return hInstance; }
	static void SetInstance(HINSTANCE hInstance);

	static int Width() { return width; }
	static void SetWidth(int width);

	static int Height() { return height; }
	static void SetHeight(int height);

	static std::wstring Title() { return title; }
	static void SetTitle(std::wstring title);
};

