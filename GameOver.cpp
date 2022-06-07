#include "GameOver.h"
#include <cstdlib>

#include "colors.h"
#include "Game.h"

GameOver::GameOver() : win(nullptr), selection(0) {
    win = newwin(6, 23, (LINES - 6) / 2, (COLS - 22) / 2);
    if(!win)
        abort();
}

GameOver::~GameOver() {
    hide();
    delwin(win);
}

void GameOver::run() {
	hide();
	while(true) {
        render();

        int ch = getch();
        if (ch == KEY_UP)
            selection = (selection + 3) % 2;
        if (ch == KEY_DOWN)
            selection = (selection + 1) % 2;
        if (ch == 'q')
            return;
        if (ch == ' ' || ch == '\n') {
            if(selection == 0) {
                hide();
                Game game;
                game.run();
				return ;
            }
            else
                return;
        }
    }
}

void GameOver::render() {
    wattron(win, COLOR_PAIR(WHITE_ON_GRAY));
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "       YOU DIED      ");
    mvwprintw(win, 2, 1, "                     ");
    wattroff(win, COLOR_PAIR(WHITE_ON_GRAY));

    short color;
    if(selection != 0)
        color = WHITE_ON_GRAY;
    else
        color = WHITE_ON_MAGENTA;

    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, 3, 1, "       restart       ");
    wattroff(win, COLOR_PAIR(color));

    if(selection != 1)
        color = WHITE_ON_GRAY;
    else
        color = WHITE_ON_MAGENTA;

    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, 4, 1, "   quit to mainmenu  ");
    wattroff(win, COLOR_PAIR(color));

    paintLogo();

    wrefresh(win);
    refresh();
}

void GameOver::hide() {
    for (int i=0; i<LINES; i++)
        for(int j=0; j<COLS; j++)
            mvaddch(i, j, ' ');
    refresh();

    for (int i=0; i<6; i++)
        mvwprintw(win, i, 0, "                      ");
    wrefresh(win);
}

void GameOver::paintLogo() {
    int x = (COLS - 76) / 2;
	mvprintw(0, x, R"(                                                                          )");
	mvprintw(1, x, R"(                                                                          )");
    mvprintw(2, x, R"(  ######\  #####\ ###\   ###|#######\   #####\  ##\   ##\#######\######\ )");
    mvprintw(3, x, R"( ##/----/ ##/--##\####\ ####|##/----/  ##/--##\ ##|   ##|##/----/##/--##\)");
    mvprintw(4, x, R"( ##|  ##\ #######|## ####/##|#####\    ##|  ##| \##\ ## /######\ ######/ )");
    mvprintw(5, x, R"( ##|  \##\##/--##|##|\## /##|##/--/    ##|  ##|  \#### / ##/--/  ##/--##\)");
    mvprintw(6, x, R"( \###### /##|  ##|##| \_/ ##|#######\  \##### /   \## /  #######\##|  ##|)");
    mvprintw(7, x, R"(  \_____/ \_/  \_/\_/     \_/\______/   \____/     \_/   \______/\_/  \_/)");
    	
	refresh(); 
}
