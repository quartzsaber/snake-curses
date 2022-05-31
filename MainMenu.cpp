#include "MainMenu.h"

#include <cstdlib>

#include "colors.h"
#include "Game.h"

MainMenu::MainMenu() : win(nullptr), selection(0) {
    win = newwin(6, 22, (LINES - 6) / 2, (COLS - 22) / 2);
    if(!win)
        abort();
}

MainMenu::~MainMenu() {
    delwin(win);
}

void MainMenu::run() {
    while(true) {
        render();
        int ch = getch();
        if (ch == KEY_UP)
            selection = (selection + 3) % 2;
        if (ch == KEY_DOWN)
            selection = (selection + 1) % 2;
        if (ch == ' ' || ch == '\n') {
            if(selection == 0) {
                delwin(win);
                /* run game */ {
                    Game game;
                    game.run();
                }
                win = newwin(6, 22, (LINES - 6) / 2, (COLS - 22) / 2);
            }
            else
                return;
        }
    }
}

void MainMenu::render() {
    wattron(win, COLOR_PAIR(WHITE_ON_BLUE));
    box(win, 0, 0);
    mvwprintw(win, 1, 1, " CURSES SNAKE CLONE ");
    mvwprintw(win, 2, 1, "                    ");
    wattroff(win, COLOR_PAIR(WHITE_ON_BLUE));

    short color;
    if(selection != 0)
        color = WHITE_ON_BLUE;
    else
        color = WHITE_ON_MAGENTA;

    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, 3, 1, "      new game      ");
    wattroff(win, COLOR_PAIR(color));

    if(selection != 1)
        color = WHITE_ON_BLUE;
    else
        color = WHITE_ON_MAGENTA;

    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, 4, 1, "        quit        ");
    wattroff(win, COLOR_PAIR(color));

    wrefresh(win);
    refresh();
}