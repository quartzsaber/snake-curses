#include <iostream>

#include <ncurses.h>

#include "colors.h"
#include "MainMenu.h"

int main() {
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    start_color();
    init_pair(WHITE_ON_BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(WHITE_ON_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    refresh();

    MainMenu menu;
    menu.run();

    endwin();
    return 0;
}

