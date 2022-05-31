#ifndef GAME_H_
#define GAME_H_

#include <ncurses.h>

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
    void scoreBoard();
    void missionBoard();

    int level;
    WINDOW* win;
    WINDOW* scoreWin;
    WINDOW* missionWin;
    GameCell board[24][24];
};

#endif
