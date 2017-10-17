// 这是主 DLL 文件。

#include "stdafx.h"

#include "EarthCLR.h"

#include "..\EarthCore\IEarthRender.h"
#if  _DEBUG
#pragma comment (lib, "EarthCored.lib")
#else
#pragma comment (lib, "EarthCore.lib")
#endif

using namespace EarthCLR;

EarthRender::EarthRender()
{
	this->pEarthRender = CreateEarthRender();
}

EarthRender::~EarthRender()
{
	DestroyEarthRender(this->pEarthRender);
}

void EarthRender::initEarth(long hwnd)
{
	pEarthRender->initEarth(hwnd);
}

void EarthRender::startRender()
{
	pEarthRender->startRender();
}

