#ifndef __REBOUND_WINDOWMANAGER_H__
#define __REBOUND_WINDOWMANAGER_H__

#include "Event.h"
#include "Window.h"

class WindowManager : public Singleton<WindowManager>, public Updatable
{
    public:
        WindowManager();
        void Update();
        void SetWindow(Window *window) { _window = window; }

        osgViewer::Viewer & GetViewer() { return _viewer; }
        osg::ref_ptr<osg::Group> GetRoot() { return _root; }
    private:
        UpdateEvent _updateEv;
        osgViewer::Viewer _viewer;
        osg::ref_ptr<osg::Group> _root;
        Window *_window;
};

#endif // __REBOUND_WINDOWMANAGER_H__