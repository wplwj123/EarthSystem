#include "Def.h"
#include "EarthRender.h"
#include "RenderThread.h"

#include <osg\Geode>
#include <osg\Node>
#include <osg\Geometry>
#include <osgViewer\Viewer>
#include <osgDB\WriteFile>
#include <osgViewer\api\win32\GraphicsWindowWin32>
#include <osgViewer\ViewerEventHandlers>
#include <osgGA\StateSetManipulator>
#include <osgGA\TrackballManipulator>
#include <OpenThreads\Thread>



void CEarthRender::release()
{
	DEBUG_INFO("%s", "");

	if (this->renderThread != NULL)
	{
		delete this->renderThread;
	}
}

void CEarthRender::initEarth(long hwnd)
{
	DEBUG_INFO("%s", "");

	RECT rect;

	// Get the client area 
	GetWindowRect((HWND)hwnd, &rect);

	// Create a WindowData struct from the Win32 Handle 
	// WindowData is used to pass in the Win32 window handle attached the GraphicsContext::Traits structure 
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData((HWND)hwnd);
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

	// Now setup the GraphicsContext::Traits by setting width, height, x position, y position etc...            
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->inheritedWindowData = windata;

	// We must set the pixelformat before we can create the OSG Rendering Surface 
	PIXELFORMATDESCRIPTOR pixelFormat =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		24,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	// Get the device context for the Win32 handle to the control 
	HDC hdc = ::GetDC((HWND)hwnd);
	if (hdc == 0)
	{
		::DestroyWindow((HWND)hwnd);
		return;
	}

	// Set the pixel format on the device context 
	int pixelFormatIndex = ::ChoosePixelFormat(hdc, &pixelFormat);
	if (pixelFormatIndex == 0)
	{
		::ReleaseDC((HWND)hwnd, hdc);
		::DestroyWindow((HWND)hwnd);
		return;
	}

	if (!::SetPixelFormat(hdc, pixelFormatIndex, &pixelFormat))
	{
		::ReleaseDC((HWND)hwnd, hdc);
		::DestroyWindow((HWND)hwnd);
		return;
	}

	// Create an Open Scene Graph graphics context 
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);

	// Create an Open Scene Graph camera 
	this->camera = new osg::Camera;

	osg::CullSettings::CullingMode cullMode = osg::CullSettings::ENABLE_ALL_CULLING;

	// Force all culling on 
	camera->setCullingMode(cullMode);

	// Set the graphics context on the camera and the viewport 
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setDrawBuffer(GL_BACK);
	camera->setReadBuffer(GL_BACK);

	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setClearColor(osg::Vec4(0.2, 0.4, 0.6, 1.0));

	// Finally, create an osgViewer instance and add the camera to it 
	this->osgViewer = new osgViewer::Viewer();
	osgViewer->setThreadingModel(osgViewer::ViewerBase::CullThreadPerCameraDrawThreadPerContext);
	//osgViewer->getCamera()->setClearColor(osg::Vec4(0.8, 0.8, 0.8, 1));
	osgViewer->getCamera()->setClearColor(osg::Vec4(0., 0., 0., 1));
	osgViewer->addSlave(camera);
	
	//create root, map node
	this->osgRoot = new osg::Group;
	this->osgMap = new osgEarth::Map;
	osg::ref_ptr<osgEarth::MapNode> mapNode = new osgEarth::MapNode(osgMap);
	osgRoot->addChild(mapNode);

	//add earth manipulator
	this->osgManip = new osgEarth::Util::EarthManipulator();
	osgManip->getSettings()->setArcViewpointTransitions(true);
	osgManip->setHomeViewpoint(osgEarth::Viewpoint("China", 110.0, 30.0, 0.0, 0.0, -90.0, (10e6) * 2));
	osgViewer->setCameraManipulator(osgManip);

	//add EventHandler
	osgViewer->addEventHandler(new osgGA::StateSetManipulator(osgViewer->getCamera()->getOrCreateStateSet()));
	osgViewer->addEventHandler(new osgViewer::LODScaleHandler);
	osgViewer->addEventHandler(new osgViewer::ThreadingHandler);
	osgViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	osgViewer->addEventHandler(new osgViewer::StatsHandler);
	osgViewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	osgViewer->addEventHandler(new osgViewer::RecordCameraPathHandler);

	osgViewer->setSceneData(osgRoot);
}

void CEarthRender::startRender()
{
	this->renderThread = new CRenderThread(this->osgViewer);

	renderThread->startThread();
}

