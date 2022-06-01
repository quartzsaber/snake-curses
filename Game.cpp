#include "Game.h"

#include <chrono>
#include <thread>

#include "colors.h"
#include "map.h"

Game::Game() : level(0), random(std::random_device()()) {
    clearBoard();
    win = newwin(24, 48, (LINES - 24) / 2, (COLS - 48) / 3);
    scoreBoard = std::make_shared<ScoreBoard>();
    snake = std::make_shared<Snake>(this);

    actors.push_back(snake);
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
    static const auto tickDuration = std::chrono::milliseconds(100);
    bool quit = false;

    draw();

    while (!quit) {
        std::this_thread::sleep_for(tickDuration);

        while (true) {
            int x = getch();
            if (x == ERR)
                break;
            else if (x == 'q')
                quit = true;
            else if (x == KEY_UP)
                snake->setDirection(Direction::UP);
            else if (x == KEY_RIGHT)
                snake->setDirection(Direction::RIGHT);
            else if (x == KEY_DOWN)
                snake->setDirection(Direction::DOWN);
            else if (x == KEY_LEFT)
                snake->setDirection(Direction::LEFT);
        }
        tick();
        draw();

        if (!snake->isAlive())
            quit = true;
    }

    //TODO: Add game over screen
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

void Game::tick() {
    std::vector<int> toRemove;
    toRemove.reserve(actors.size());

    for (int i=0; i<actors.size(); i++) {
        if (!actors[i]->tick(this))
            toRemove.push_back(i);
    }

    for (int i = toRemove.size() - 1; i >= 0; i--) {
        actors.erase(actors.begin() + toRemove[i]);
    }
}

void Game::draw() {
    clearBoard();

    for (auto& actor : actors)
        actor->draw(this);

    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            short color;
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
                case GameCell::SNAKE_HEAD:
                    color = WHITE_ON_YELLOW;
                    break;
                case GameCell::SNAKE_TRAIL:
                    color = WHITE_ON_ORANGE;
                    break;
                default:
                    color = WHITE_ON_BLUE;
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

int Game::getRandomNumber() {
    return static_cast<int>(random() & 0x7FFFFFFF);
}
