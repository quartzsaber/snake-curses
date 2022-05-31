#ifndef SCORE_BOARD_H_
#define SCORE_BOARD_H_

#include <ncurses.h>

class ScoreBoard {
public:
    ScoreBoard();
    ScoreBoard(const ScoreBoard& copy) = delete;
    ScoreBoard(ScoreBoard&& move) = delete;
    ~ScoreBoard();

    void draw();

private:
    void drawScore();
    void drawMission();

    WINDOW* scoreWin;
    WINDOW* missionWin;
};

#endif
