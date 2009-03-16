#ifndef __REBOUND_GAMEWINDOW_H__
#define __REBOUND_GAMEWINDOW_H__

#include "Window.h"
#include "GameModel.h"

class GameWindow : public Window
{
    public:
        GameWindow();
    private:
        GameModel _model;
};

#endif //__REBOUND_GAMEWINDOW_H__