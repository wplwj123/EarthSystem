#include "Def.h"
#include "RenderThread.h"

#include <OpenThreads\Mutex>
#include <OpenThreads\Thread>
#include <osgViewer\Viewer>

CRenderThread::~CRenderThread() 
{
	DEBUG_INFO("%s", "");
	cancel();
	while (isRunning())
	{
		OpenThreads::Thread::YieldCurrentThread();
	}
}

void CRenderThread::run()
{
	DEBUG_INFO("%s", "");

	if (!this->_osgViewer->isRealized())
	{
		_osgViewer->realize();
	}

	this->_osgViewer->setDone(false);

	while (!this->_osgViewer->done() && !this->_done)
	{
		this->_osgViewer->frame();
	}
}

int CRenderThread::cancel()
{
	DEBUG_INFO("%s", "");
	_done = true;
	this->_osgViewer->setDone(true);
	return 0;
}
