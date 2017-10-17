#pragma once


#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

#define COMMON_EXPORTS

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

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

//�滻������  
#ifndef _DEBUG  
#define LOGFUNC(...) ((void)0)  
#else  
#define LOGFUNC(...) (printf(__VA_ARGS__))  
#endif  

//��ǰ�����##���������ڣ����ɱ�����ĸ���Ϊ0ʱ�������## �𵽰�ǰ������","ȥ��������  
#define DEBUG_INFO(format, ...) printf("File:%s, Line:%d, Function:%s, %s\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);