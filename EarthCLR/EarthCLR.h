// EarthCLR.h

#pragma once

using namespace System;

class IEarthRender;

namespace EarthCLR {

	public ref class EarthRender
	{
	public:
		EarthRender();
		~EarthRender();

		void initEarth(long hwnd);

		void startRender();

	private:
		IEarthRender *pEarthRender;
	};
}
