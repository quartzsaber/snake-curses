#include "Game.h"

#include <chrono>
#include <thread>

#include "colors.h"
#include "map.h"
#include "ItemGrowth.h"
#include "ItemPoison.h"
#include "Gate.h"
#include "GameOver.h"

Game::Game() : level(0), ticks(0), lastItemSpawnTick(5), delayUptoTicks(0), random(std::random_device()()) {
    clearBoard();
    win = newwin(24, 48, (LINES - 24) / 2, (COLS - 48) / 3);
    scoreBoard = std::make_shared<ScoreBoard>(this);

    actors.push_back(std::make_shared<Snake>(this));
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
    static const auto tickDuration = std::chrono::milliseconds(300);
    bool quit = false;

    level = 0;
    ticks = 0;
    lastItemSpawnTick = 0;
    delayUptoTicks = 5;

    draw();

    while (!quit) {
        std::shared_ptr<Snake> snake = getSnake();
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
	GameOver menu;
	menu.run();
}

void Game::advanceLevel() {
    if (level < 5) {
        level++;
        actors.clear();
        actors.push_back(std::make_shared<Snake>(this));
        delayUptoTicks = ticks + 5;
    }
}

std::shared_ptr<Snake> Game::getSnake() {
    return std::dynamic_pointer_cast<Snake>(
        findActor([](const std::shared_ptr<IActor> ptr) -> bool {
            return dynamic_cast<Snake*>(ptr.get()) != nullptr;
        })
    );
}

int Game::countItems() {
    int cnt = 0;

    for (auto& ptr : actors) {
        if (dynamic_cast<ItemGrowth*>(ptr.get()) != nullptr ||
            dynamic_cast<ItemPoison*>(ptr.get()) != nullptr)
            cnt++;
    }

    return cnt;
}

int Game::countGate() {
    int cnt = 0;

    for (auto& ptr : actors) {
        if (dynamic_cast<Gate*>(ptr.get()) != nullptr)
            cnt++;
    }

    return cnt;
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
    std::shared_ptr<Snake> snake = getSnake();
    if (snake == nullptr)
        return;

    ticks++;
    if (ticks < delayUptoTicks)
        return;

    if (lastItemSpawnTick + 15 <= ticks && getRandomNumber() >= 8192) {
        lastItemSpawnTick = ticks;
        switch (getRandomNumber() % 3) {
        case 0:
            if (countItems() >= 3)
                break;
            actors.push_back(std::make_shared<ItemGrowth>(this));
            break;
        case 1:
            if (countItems() >= 3)
                break;
            actors.push_back(std::make_shared<ItemPoison>(this));
            break;
        case 2:
            if (countGate() >= 1)
                break;
            actors.push_back(std::make_shared<Gate>(this));
            break;
        }
    }

    std::vector<int> toRemove;
    toRemove.reserve(actors.size());
	
	snake->isDead();

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
                case GameCell::GROWTH:
                    color = WHITE_ON_GREEN;
                    break;
                case GameCell::POISON:
                    color = WHITE_ON_RED;
                    break;
                case GameCell::GATE:
                    color = WHITE_ON_MAGENTA;
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
