#include <iostream>

#include <ncurses.h>

#include "colors.h"
#include "MainMenu.h"

int main() {
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    nodelay(stdscr, true);
    curs_set(0);
    start_color();
    if (COLORS < MAX_COLORS || COLOR_PAIRS < MAX_COLOR_PAIRS) {
        printw("Insufficient color supported by terminal.");
        while (getch() != ERR);
        return 0;
    }
    init_color(COLOR_GRAY, 500, 500, 500);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_ORANGE, 1000, 500, 0);
    init_pair(WHITE_ON_BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(WHITE_ON_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(WHITE_ON_GREEN, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(WHITE_ON_GRAY, COLOR_WHITE, COLOR_GRAY);
    init_pair(WHITE_ON_YELLOW, COLOR_WHITE, COLOR_YELLOW);
    init_pair(WHITE_ON_ORANGE, COLOR_WHITE, COLOR_ORANGE);
    refresh();

    /* main menu */ {
        MainMenu menu;
        menu.run();
    }

    endwin();
    return 0;
}

