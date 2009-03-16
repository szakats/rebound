#ifndef __REBOUND_MENU_H__
#define __REBOUND_MENU_H__

#include "Window.h"

class Menu : public Window
{
    public:
        class MenuItemBase
        {
            public:
                MenuItemBase(std::string text) : _text(text) {}
                virtual void Call() = 0;
                std::string GetText() { return _text; }
            private:
                std::string _text;
        };
        
        template<class T>
        class MenuItem : public MenuItemBase
        {
            public:
                typedef void (T::*Method)();
                MenuItem(std::string text, T* menu, Method method)
                    : MenuItemBase(text), _menu(menu), _method(method) {}
                void Call() { (_menu->*_method)(); }
            private:
                Method _method; 
                T* _menu;
        };

        Menu(Window *window) : Window(window) {}

        void AddItem(MenuItemBase *menuItem)
        {
            _menuItems.push_back(menuItem);
        }

        void Draw();

    private:
        typedef std::list<MenuItemBase *> MenuItemList;
        MenuItemList _menuItems;
};

class MainMenu : public Menu
{
    public:
        MainMenu(Window * window);
        void NewGame();
        void JoinGame();
        void Quit();
};

#endif //__REBOUND_MENU_H__