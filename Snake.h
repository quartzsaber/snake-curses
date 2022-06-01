#ifndef SNAKE_H_
#define SNAKE_H_

#include <deque>

#include "IActor.h"

class Snake : public IActor {
public:
    explicit Snake(Game* game);
    Snake(const Snake& copy) = delete;
    Snake(Snake&& move) = delete;

    ~Snake();

    bool tick(Game* game) override;
    void draw(Game* game) override;

    void setDirection(Direction newDir) { dir = newDir; }

private:
    Coord pos;
    Direction dir;
    std::deque<Coord> trail;
};

#endif
