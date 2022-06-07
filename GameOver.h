#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#include <ncurses.h>

class GameOver {
public:
    GameOver();
    GameOver(const GameOver& copy) = delete;
    GameOver(GameOver&& move) = delete;
    ~GameOver();
   void run();

private:
    void render();
    void hide();
    void paintLogo();
	
    WINDOW* win;
    int selection;
};

#endif
