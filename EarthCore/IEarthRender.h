#pragma once

#ifdef COMMON_EXPORTS
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif

/*
≥°æ∞‰÷»æ¿‡
*/

class IEarthRender
{
public:
	virtual void release() = 0;

	virtual void initEarth(long hwnd) = 0;

	virtual void startRender() = 0;

};

extern "C" COMMON_API IEarthRender* _stdcall CreateEarthRender();

extern "C" COMMON_API void _stdcall DestroyEarthRender(IEarthRender* pEarthRender);

