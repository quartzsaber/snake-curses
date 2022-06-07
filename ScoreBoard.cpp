#include "ScoreBoard.h"
#include "Game.h"
#include "Snake.h"

#include <cstdlib>

static const int mission[6][4] = {
    {5, 1, 0, 0},
    {7, 2, 2, 1},
    {9, 3, 4, 2},
    {11, 5, 6, 3},
    {13, 8, 8, 4},
    {15, 13, 10, 5},
};

ScoreBoard::ScoreBoard(Game *game) : game(game) {
    scoreWin = newwin(7, 24, (LINES - 7) / 3, (COLS - 24) * 4 / 5);
    missionWin = newwin(7, 24, (LINES - 7) * 2 / 3, (COLS - 24) * 4 / 5);

    for(int i=0; i<4; i++)
        success[i] = ' ';

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
    std::shared_ptr<Snake> snake = game->getSnake();
    if(snake == nullptr) 
        return;

    if(snake->getLength() >= mission[game->level][0])
        success[0] = 'v';
    else
        success[0] = ' ';

    if(snake->countGrowth >= mission[game->level][1])
        success[1] = 'v';
    else
        success[1] = ' ';
        
    if(snake->countPoison >= mission[game->level][2])
        success[2] = 'v';
    else
        success[2] = ' ';
        
    if(snake->countGate >= mission[game->level][3])
        success[3] = 'v';
    else
        success[3] = ' ';
    
    int successCount = 0;
    for (int i=0; i<4; i++)
        if (success[i] == 'v')
            successCount++;
    
    if (successCount == 4)
        game->advanceLevel();

    for (int i=0; i<7; i++)
        for (int j=0; j<24; j++)
            mvwprintw(scoreWin, i, j, " ");

    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 1, 1, "Score Board");
    mvwprintw(scoreWin, 2, 1, "  B:  %d / %d", snake->getLength(), mission[game->level][0]);
    mvwprintw(scoreWin, 3, 1, "  +:  %d", snake->countGrowth);
    mvwprintw(scoreWin, 4, 1, "  -:  %d", snake->countPoison);
    mvwprintw(scoreWin, 5, 1, "  G:  %d", snake->countGate);
}

void ScoreBoard::drawMission() {
    for (int i=0; i<7; i++)
        for (int j=0; j<24; j++)
            mvwprintw(missionWin, i, j, " ");

    box(missionWin, 0, 0);
    mvwprintw(missionWin, 1, 1, "Mission");
    mvwprintw(missionWin, 2, 1, "  B:  %d (%c)", mission[game->level][0], success[0]);
    mvwprintw(missionWin, 3, 1, "  +:  %d (%c)", mission[game->level][1], success[1]);
    mvwprintw(missionWin, 4, 1, "  -:  %d (%c)", mission[game->level][2], success[2]);
    mvwprintw(missionWin, 5, 1, "  G:  %d (%c)", mission[game->level][3], success[3]);
}
