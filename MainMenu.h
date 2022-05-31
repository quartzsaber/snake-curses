#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <ncurses.h>

class MainMenu {
public:
    MainMenu();
    MainMenu(const MainMenu& copy) = delete;
    MainMenu(MainMenu&& move) = delete;
    ~MainMenu();

    void run();

private:
    void render();
    void hide();

    WINDOW* win;
    int selection;
};

#endif
