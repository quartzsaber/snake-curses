#include "Game.h"
#include "item.h"

#include "colors.h"
#include "map.h"

Game::Game() : level(0) {
    clearBoard();
    win = newwin(24, 48, (LINES - 24) / 2, (COLS - 48) / 3);
    scoreBoard = std::make_shared<ScoreBoard>();
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
    itemcnt=0;
    draw();
    while (true) {
        int x = getch();
        if (x != ERR)
            break;
    }
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
            if ((i == 0 || board[i-1][j] == GameCell::WALL) &&
                (i == 23 || board[i+1][j] == GameCell::WALL) &&
                (j == 0 || board[i][j-1] == GameCell::WALL) &&
                (j == 23 || board[i][j+1] == GameCell::WALL))
                board[i][j] = GameCell::IMMUNE_WALL;
        }
    }
}

void Game::itemSpawn(){
    //TODO[info]: Need to implement rand function
    int x = 24,y = 24;
    if (board[x][y] == GameCell::EMPTY) {
		int type = 3;
		//TODO[INFO]: After the implementation of the tick function, After the item deswpawns, the itemcnt should be decreased.
		//TODO[INFO]: After the implementation of the tick function, After every tick passed the lifespan should be decreased.
				
		if (type == 0) {
			ItemPosion tmp;
			tmp.pos={x,y};
			tmp.lifespan=4;
			items.push_back(std::make_shared<Item>(tmp));
			itemcnt++;
	
		}
		else if (type == 1) {
			ItemGrowth tmp;
			tmp.pos={x,y};
			tmp.lifespan=4;
			items.push_back(std::make_shared<Item>(tmp));
			itemcnt++;
		}
    }
	//TODO [INFO]: Gate will be Spawned separately.
}
void Game::draw() {
    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            short color = WHITE_ON_BLUE;
            switch(board[i][j]) {
                case GameCell::EMPTY:
                    color = WHITE_ON_BLUE;
                    break;
                case GameCell::WALL:
                    color = BLACK_ON_WHITE;
                    break;
                case GameCell::IMMUNE_WALL:
                    color = WHITE_ON_GRAY;
                    break;
            }
            wattron(win, COLOR_PAIR(color));
            mvwprintw(win, i, j * 2, "  ");
            wattroff(win, COLOR_PAIR(color));
        }
    }
    
    scoreBoard->draw();

    wrefresh(win);
    refresh();
}
