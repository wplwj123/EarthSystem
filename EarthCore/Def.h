#pragma once


#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#define COMMON_EXPORTS

// TODO: 在此处引用程序需要的其他头文件

#ifdef _DEBUG  
#pragma comment (lib, "osgd.lib")
#pragma comment (lib, "osgDBd.lib")
#pragma comment (lib, "osgGAd.lib")
#pragma comment (lib, "osgViewerd.lib")
#pragma comment (lib, "osgEarthd.lib")
#pragma comment (lib, "osgEarthUtild.lib")
#pragma comment (lib, "OpenThreadsd.lib")
#else  
#pragma comment (lib, "osg.lib")
#pragma comment (lib, "osgDB.lib")
#pragma comment (lib, "osgGA.lib")
#pragma comment (lib, "osgViewer.lib")
#pragma comment (lib, "osgEarth.lib")
#pragma comment (lib, "osgEarthUtil.lib")
#pragma comment (lib, "OpenThreads.lib")
#endif 


#include <cstdlib>
#include <cstdio>
using namespace std;

//替换函数名  
#ifndef _DEBUG  
#define LOGFUNC(...) ((void)0)  
#else  
#define LOGFUNC(...) (printf(__VA_ARGS__))  
#endif  

//宏前面加上##的作用在于：当可变参数的个数为0时，这里的## 起到把前面多余的","去掉的作用  
#define DEBUG_INFO(format, ...) printf("File:%s, Line:%d, Function:%s, %s\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);