#include "Game.h"

#include "colors.h"
#include "map.h"

Game::Game() : level(0) {
    clearBoard();
    win = newwin(24, 48, (LINES - 24) / 2, (COLS - 48) / 3);
    scoreWin = newwin(7, 24, (LINES - 7) / 3, (COLS - 24));
    missionWin = newwin(7, 24, (LINES - 7) * 2 / 3, (COLS - 24));
}

Game::~Game() {
    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            mvwprintw(win, i, j * 2, "  ");
        }
    }

    for (int i=0; i<7; i++) {
        for (int j=0; j<24; j++) {
            mvwprintw(scoreWin, i, j, " ");
            mvwprintw(missionWin, i, j, " ");
        }
    }

    wrefresh(win);
    wrefresh(scoreWin);
    wrefresh(missionWin);
    delwin(win);
}

void Game::run() {
    draw();
    getch();
}

void Game::clearBoard() {
    for (int i=0; i<24; i++) {
        for (int j=0; j<3; j++) {
            unsigned char num = mapData[level][i * 3 + j];
            for (int k=0; k<8; k++) {
                if (num & 0x80)
                    board[i][j * 8 + k] = GameCell::WALL;
                else
                    board[i][j * 8 + k] = GameCell::EMPTY;
                num <<= 1;
            }
        }
    }

    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            int cnt = 0;
            if ((i == 0 || board[i-1][j] == GameCell::WALL) &&
                (i == 23 || board[i+1][j] == GameCell::WALL) &&
                (j == 0 || board[i][j-1] == GameCell::WALL) &&
                (j == 23 || board[i][j+1] == GameCell::WALL))
                board[i][j] = GameCell::IMMUNE_WALL;
        }
    }
}

void Game::draw() {
    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            short color;
            switch(board[i][j]) {
                case GameCell::EMPTY:
                    color = WHITE_ON_BLUE;
                    break;
                case GameCell::WALL:
                case GameCell::IMMUNE_WALL:
                    color = BLACK_ON_WHITE;
                    break;
            }
            wattron(win, COLOR_PAIR(color));
            mvwprintw(win, i, j * 2, "  ");
            wattroff(win, COLOR_PAIR(color));
        }
    }
    
    scoreBoard();
    missionBoard();

    wrefresh(win);
    wrefresh(scoreWin);
    wrefresh(missionWin);
    refresh();
}

void Game::scoreBoard() {
    for (int i=0; i<7; i++)
        for (int j=0; j<24; j++)
            mvwprintw(scoreWin, i, j, " ");

    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 1, 1, "Score Board");
    mvwprintw(scoreWin, 2, 1, "  B:  %d");
    mvwprintw(scoreWin, 3, 1, "  +:  %d");
    mvwprintw(scoreWin, 4, 1, "  -:  %d");
    mvwprintw(scoreWin, 5, 1, "  G:  %d");
}

void Game::missionBoard() {
    for (int i=0; i<7; i++)
        for (int j=0; j<24; j++)
            mvwprintw(missionWin, i, j, " ");

    box(missionWin, 0, 0);
    mvwprintw(missionWin, 1, 1, "Mission");
    mvwprintw(missionWin, 2, 1, "  B:  %4d / %-4d");
    mvwprintw(missionWin, 3, 1, "  +:  %4d / %-4d");
    mvwprintw(missionWin, 4, 1, "  -:  %4d / %-4d");
    mvwprintw(missionWin, 5, 1, "  G:  %4d / %-4d");
}