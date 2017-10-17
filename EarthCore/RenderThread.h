#pragma once
#include <osg/ref_ptr>
#include <OpenThreads\Thread>

namespace osgViewer {
	class Viewer;
}

class CRenderThread : public OpenThreads::Thread
{
public:

	CRenderThread(osgViewer::Viewer* viewer) : _done(false), _osgViewer(viewer) {};
	~CRenderThread();
	void run();

	int cancel();

private:
	bool _done;

	osg::ref_ptr<osgViewer::Viewer> _osgViewer;
};
