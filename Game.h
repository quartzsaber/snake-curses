#ifndef GAME_H_
#define GAME_H_

class Game {
public:
    Game();
    Game(const Game& copy) = delete;
    Game(Game&& move) = delete;
    ~Game();

    void run();
};

#endif
