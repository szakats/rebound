#include "common.h"

#include <string>
#include "Menu.h"


MainMenu::MainMenu(Window *window) : Menu(window)
{
    AddItem(new MenuItem<MainMenu>("Host Game", this, &MainMenu::NewGame));
    AddItem(new MenuItem<MainMenu>("Join Game", this, &MainMenu::JoinGame));
    AddItem(new MenuItem<MainMenu>("Quit", this, &MainMenu::Quit));

    Draw();

}

void MainMenu::NewGame()
{

}

void MainMenu::JoinGame()
{

}

void MainMenu::Quit()
{

}