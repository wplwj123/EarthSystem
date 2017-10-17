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

	// ��ʾ����    
	ShowWindow(hwnd, SW_SHOW);

	IEarthRender* earthRender = CreateEarthRender();
	earthRender->initEarth((long)hwnd);

	// ���´���    
	UpdateWindow(hwnd);

	earthRender->startRender();

	// ��Ϣѭ��    
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
		_T("DDraw"),           //����ע���������Ҫ��ȫһ��    
		L"����",  //���ڱ�������    
		WS_OVERLAPPEDWINDOW, //���������ʽ    
		38,             //��������ڸ�����X����    
		20,             //��������ڸ�����Y����    
		1024,                //���ڵĿ��    
		768,                //���ڵĸ߶�    
		NULL,               //û�и����ڣ�ΪNULL    
		NULL,               //û�в˵���ΪNULL    
		hInstance,          //��ǰӦ�ó����ʵ�����    
		NULL);              //û�и������ݣ�ΪNULL    

	return hwnd;
}

// ��Ϣ��������ʵ��
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