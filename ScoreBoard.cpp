#include "ScoreBoard.h"

#include <cstdlib>

ScoreBoard::ScoreBoard() {
    scoreWin = newwin(7, 24, (LINES - 7) / 3, (COLS - 24) * 4 / 5);
    missionWin = newwin(7, 24, (LINES - 7) * 2 / 3, (COLS - 24) * 4 / 5);

    if(!scoreWin || !missionWin)
        abort();
}

ScoreBoard::~ScoreBoard() {
    for (int i=0; i<7; i++) {
        for (int j=0; j<24; j++) {
            mvwprintw(scoreWin, i, j, " ");
            mvwprintw(missionWin, i, j, " ");
        }
    }
    wrefresh(scoreWin);
    wrefresh(missionWin);
    delwin(scoreWin);
    delwin(missionWin);
}

void ScoreBoard::draw() {
    drawScore();
    drawMission();
    wrefresh(scoreWin);
    wrefresh(missionWin);
}

void ScoreBoard::drawScore() {
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

void ScoreBoard::drawMission() {
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
