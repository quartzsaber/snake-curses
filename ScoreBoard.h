#ifndef SCORE_BOARD_H_
#define SCORE_BOARD_H_

#include <ncurses.h>

class Game;

class ScoreBoard {
public:
    explicit ScoreBoard(Game *game);
    ScoreBoard(const ScoreBoard& copy) = delete;
    ScoreBoard(ScoreBoard&& move) = delete;
    ~ScoreBoard();

    void draw();

private:
    void drawScore();
    void drawMission();

    WINDOW* scoreWin;
    WINDOW* missionWin;

    Game *game;

    char success[4];
};

#endif
