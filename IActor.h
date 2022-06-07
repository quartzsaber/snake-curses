#ifndef IACTOR_H_
#define IACTOR_H_

#include "GameCell.h"

class Game;

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Coord {
    int y, x;

    Coord& operator+=(const Direction dir) {
        static const Coord delta[4] = {
            { -1,  0 },
            {  0,  1 },
            {  1,  0 },
            {  0, -1 },
        };

        const Coord& movement = delta[static_cast<int>(dir)];
        y += movement.y;
        x += movement.x;
        return *this;
    }

    Coord operator+(const Direction dir) const {
        Coord ret = *this;
        ret += dir;
        return ret;
    }
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
