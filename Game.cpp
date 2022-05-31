#include "Game.h"

#include "colors.h"

Game::Game() : level(0) {
    clearBoard();
    win = newwin(24, 48, (LINES - 24) / 2, (COLS - 48) / 3);
}

Game::~Game() {
    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            mvwprintw(win, i, j * 2, "  ");
        }
    }

    wrefresh(win);
    delwin(win);
}

void Game::run() {
    draw();
    getch();
}

void Game::clearBoard() {
    for(int i=0; i<24; i++) {
        for(int j=0; j<24; j++) {
            board[i][j] = GameCell::EMPTY;
        }
    }

    for(int i=0; i<24; i++) {
        board[0][i] = GameCell::WALL;
        board[23][i] = GameCell::WALL;
        board[i][0] = GameCell::WALL;
        board[i][23] = GameCell::WALL;
    }

    board[0][0] = GameCell::IMMUNE_WALL;
    board[0][23] = GameCell::IMMUNE_WALL;
    board[23][0] = GameCell::IMMUNE_WALL;
    board[23][23] = GameCell::IMMUNE_WALL;
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
    
    wrefresh(win);
    refresh();
}