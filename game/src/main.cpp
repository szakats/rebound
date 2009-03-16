#include "common.h"

#include <Controller.h>
#include "EventScheduler.h"
#include "WindowManager.h"
#include "GameWindow.h"
#include "Menu.h"

#include <osg/DeleteHandler>
#include <osgAl/SoundManager>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
//    WebCamController c;
//    c.test();

    putenv("PATH=D:\\rebound\\OpenSceneGraph-2.8.0-rc2\\build\\bin\\");
    putenv("OSG_FILE_PATH=D:\\rebound\\osgal-0.6.1\\bin\\");
    putenv("OSG_LIBRARY_PATH=D:\\rebound\\OpenSceneGraph-2.8.0-rc2\\build\\bin\\");

    // initialize the scheduler
    EventScheduler::Instance();

    // initialize the first window
    WindowManager::Instance().SetWindow(new MainMenu(NULL));

    EventScheduler::Instance().Run();

	if (osg::Referenced::getDeleteHandler()) {
		osg::Referenced::getDeleteHandler()->setNumFramesToRetainObjects(0);
		osg::Referenced::getDeleteHandler()->flushAll();
	}
	osgAL::SoundManager::instance()->shutdown();
	return 0;
}
