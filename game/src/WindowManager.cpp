#include "common.h"

#include "WindowManager.h"
// passing 'this' to the UpdateEvent shouldn't be a problem
// as long as it doesn't call something in WindowManager in its constructor
#pragma warning(disable:4355)

WindowManager::WindowManager() 
    : _updateEv(0, 20, this),  // 50fps
      _root(new osg::Group)
{
    _viewer.setSceneData( _root );

    //_viewer.realize();
}

void WindowManager::Update()
{
    //_viewer.run();
    if(!_viewer.done())
    {
        _viewer.frame();
    }
    else 
        QuitEvent::Quit(0);

    //printf("I'm called\n");
    return;
}