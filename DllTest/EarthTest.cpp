#include <iostream>
using namespace std;

#include <Windows.h>
#include <tchar.h>

#include "..\EarthCore\IEarthRender.h"
#if  _DEBUG
#pragma comment (lib, "EarthCored.lib")
#else
#pragma comment (lib, "EarthCore.lib")
#endif

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
HWND createRenderWindow();

int main(int argc, char* argv[])
{
	HWND hwnd = createRenderWindow();

	// 显示窗口    
	ShowWindow(hwnd, SW_SHOW);

	IEarthRender* earthRender = CreateEarthRender();
	earthRender->initEarth((long)hwnd);

	// 更新窗口    
	UpdateWindow(hwnd);

	earthRender->startRender();

	// 消息循环    
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyEarthRender(earthRender);

	return 0;
}

HWND createRenderWindow()
{
	HINSTANCE hInstance;
	hInstance = GetModuleHandle(NULL);
	WNDCLASS Draw;
	Draw.cbClsExtra = 0;
	Draw.cbWndExtra = 0;
	Draw.hCursor = LoadCursor(hInstance, IDC_ARROW);;
	Draw.hIcon = LoadIcon(hInstance, IDI_APPLICATION);;
	Draw.lpszMenuName = NULL;
	Draw.style = CS_HREDRAW | CS_VREDRAW;
	Draw.hbrBackground = (HBRUSH)COLOR_WINDOW;
	Draw.lpfnWndProc = WindowProc;
	Draw.lpszClassName = _T("DDraw");
	Draw.hInstance = hInstance;


	RegisterClass(&Draw);

	HWND hwnd = CreateWindow(
		_T("DDraw"),           //上面注册的类名，要完全一致    
		L"绘制",  //窗口标题文字    
		WS_OVERLAPPEDWINDOW, //窗口外观样式    
		38,             //窗口相对于父级的X坐标    
		20,             //窗口相对于父级的Y坐标    
		1024,                //窗口的宽度    
		768,                //窗口的高度    
		NULL,               //没有父窗口，为NULL    
		NULL,               //没有菜单，为NULL    
		hInstance,          //当前应用程序的实例句柄    
		NULL);              //没有附加数据，为NULL    

	return hwnd;
}

// 消息处理函数的实现
LRESULT CALLBACK WindowProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}