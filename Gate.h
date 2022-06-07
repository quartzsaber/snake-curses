#ifndef GATE_H_
#define GATE_H_

#include "IActor.h"

class Gate : public IActor {
public:
    explicit Gate(Game* game);
    Gate(const Gate& copy) = delete;
    Gate(Gate&& move) = delete;
    
    virtual ~Gate();

    bool tick(Game* game) override;
    void draw(Game* game) override;

    int findIndex(Coord pos);
    Coord getPos(int idx);
    Direction fixDirection(int idx, Direction dir);

private:
    bool flagAlive;
    Game* game;
    Coord pos[2];
};

#endif
