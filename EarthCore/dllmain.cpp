// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "Def.h"

#include "EarthRender.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

COMMON_API IEarthRender* APIENTRY CreateEarthRender()
{
	return new CEarthRender();
}

COMMON_API void APIENTRY DestroyEarthRender(IEarthRender* pEarthRender)
{
	pEarthRender->release();
	delete pEarthRender;
}
