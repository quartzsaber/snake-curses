#ifndef IACTOR_H_
#define IACTOR_H_

#include "GameCell.h"

class Game;

struct Coord {
    int y, x;
};

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class IActor {
public:
    IActor() = default;
    IActor(const IActor& copy) = delete;
    IActor(IActor&& move) = delete;

    virtual ~IActor() {}

    // 여기서 false 를 리턴하면 오브젝트가 지워짐
    virtual bool tick(Game* game) = 0;

    // board에 자기 자신을 그림
    virtual void draw(Game* game) = 0;
};

#endif
