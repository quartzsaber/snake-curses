#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include <random>

#include <ncurses.h>

#include "ScoreBoard.h"
#include "GameCell.h"
#include "IActor.h"
#include "Snake.h"

class Game {
public:
    Game();
    Game(const Game& copy) = delete;
    Game(Game&& move) = delete;
    ~Game();

    void run();

    int getCurrentTick() { return ticks; }
    int getRandomNumber();
    Board& getBoard() { return board; }

    template<class Fn>
    void filterActor(const Fn& filter) {
        std::vector<int> toRemove;
        for (int i=0; i<actors.size(); i++) {
            if (!filter(actors[i]))
                toRemove.push_back(i);
        }
        for (int i=toRemove.size()-1; i >= 0; i--)
            actors.erase(actors.begin() + toRemove[i]);
    }

private:
    // Growth 와 Poison의 갯수를 샌다
    int countItems();

    void clearBoard();
    void draw();
    void tick();

	int level;
    int ticks;
    int lastItemSpawnTick;
    WINDOW* win;
    std::shared_ptr<Snake> snake;
    std::shared_ptr<ScoreBoard> scoreBoard;
    std::vector<std::shared_ptr<IActor>> actors;
    std::mt19937 random;
    Board board;
};

#endif
