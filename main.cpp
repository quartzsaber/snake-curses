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
    curs_set(0);
    init_color(COLOR_CYAN, 500, 500, 500);
    init_pair(WHITE_ON_BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(WHITE_ON_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(WHITE_ON_GREEN, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(WHITE_ON_GRAY, COLOR_WHITE, COLOR_CYAN);
    refresh();

    /* main menu */ {
        MainMenu menu;
        menu.run();
    }

    endwin();
    return 0;
}

