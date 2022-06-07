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
	void isDead() { if(trail.size()<2){ flagAlive = 0; } return;}
    bool isAlive() { return flagAlive; }
    void setDirection(Direction newDir) { dir = newDir; }

    int getLength() { return trail.size() + 1; }

    int countGrowth;
    int countPoison;
    int countGate;
	
private:
    bool flagAlive;
    Coord pos;
    Direction dir;
    std::deque<Coord> trail;
};

#endif
