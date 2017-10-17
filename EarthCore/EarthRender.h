#pragma once

#include "IEarthRender.h"
#include "RenderThread.h"
#include <osgViewer\Viewer>
#include <osg\Camera>
#include <osgEarth\MapNode>
#include <osgEarthUtil\EarthManipulator>

/*
	≥°æ∞‰÷»æ¿‡
*/
class CEarthRender : public IEarthRender
{
public:
	void release();

	void initEarth(long hwnd);

	void startRender();

private:

	osg::ref_ptr<osg::Camera> camera;

	osg::ref_ptr<osgViewer::Viewer> osgViewer;

	osg::ref_ptr<osg::Group> osgRoot;

	osg::ref_ptr<osgEarth::Map> osgMap;

	osg::ref_ptr<osgEarth::Util::EarthManipulator> osgManip;

	CRenderThread* renderThread;
};
