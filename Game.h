#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include <vector>

#include <ncurses.h>

#include "ScoreBoard.h"

#include "item.h"

enum class GameCell : unsigned char {
	UNKNOWN = 0,
	GROWTH,
	POISON,
	PORTAL,
    IMMUNE_WALL,
	WALL,
	SNAKE_HEAD,
	SNAKE_TRAIL,
	EMPTY
};

class Game {
public:
    Game();
    Game(const Game& copy) = delete;
    Game(Game&& move) = delete;
    ~Game();

    void run();

private:
    void clearBoard();
    void draw();
	void itemSpawn();
    int itemcnt;
	int level;
    std::shared_ptr<ScoreBoard> scoreBoard;
    WINDOW* win;
    GameCell board[24][24];
    std::vector<std::shared_ptr<Item>> items;
};

#endif
