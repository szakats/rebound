#ifndef __REBOUND_WINDOW_H__
#define __REBOUND_WINDOW_H__

#include "Event.h"

class Window
{
    public:
        Window(Window *parent);
        virtual ~Window() {}
    private:
        Window *parent;
};

#endif //__REBOUND_WINDOW_H__