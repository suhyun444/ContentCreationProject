#include "Window.h"

int Window::width;
int Window::height;
std::wstring Window::title;
HWND Window::hwnd;
HINSTANCE Window::hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;

	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(NULL, TEXT("종료하시겠습니까?"), TEXT("종료"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(hwnd);
			}
		}
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
bool Window::InitializeWindow()
{
	return InitializeWindow(hInstance, width, height, title);
}
bool Window::InitializeWindow(HINSTANCE hInstance, int width, int height, std::wstring title)
{
	Window::hInstance = hInstance;
	Window::width = width;
	Window::height = height;
	Window::title = title;
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.lpszClassName = TEXT("PhysicsEngine");
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpfnWndProc = WindowProc;

	if (RegisterClass(&wc) == false) {
		MessageBoxW(nullptr, L"클래스 등록 실패", L"오류", 0);
		exit(-1);
	}
	RECT rect = { 0,0,width,height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	Window::width = rect.right - rect.left;
	Window::height = rect.bottom - rect.top;

	hwnd = CreateWindow(wc.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0,
		Window::width, Window::height, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBoxW(nullptr, L"윈도우 생성 실패", L"오류", 0);
		return false;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return true;
}

void Window::SetInstance(HINSTANCE hInstance)
{
	Window::hInstance = hInstance;
}

void Window::SetWidth(int width)
{
	Window::width = width;
}

void Window::SetHeight(int height)
{
	Window::height = height;
}

void Window::SetTitle(std::wstring title)
{
	Window::title = title;
}