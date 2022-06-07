#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#include <ncurses.h>

class GameOver {
public:
    GameOver();
    GameOver(const GameOver& copy) = delete;
    GameOver(GameOver&& move) = delete;
    ~GameOver();

    void run(int score);

private:
    void render(int score);
    void hide();
    void paintLogo(int score);

    WINDOW* win;
    int selection;
};

#endif
