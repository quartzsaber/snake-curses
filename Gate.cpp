#include "Gate.h"

#include <cassert>
#include <vector>

#include "Game.h"

static bool checkNotWall(Game* game, Coord c) {
    if (0 <= c.x && c.x < 24 && 0 <= c.y && c.y < 24
            && game->getBoard()[c.y][c.x] != GameCell::WALL
            && game->getBoard()[c.y][c.x] != GameCell::IMMUNE_WALL)
        return true;
    return false;
}

Gate::Gate(Game* game_) : flagAlive(true), game(game_) {
    std::vector<Coord> spawnables;
    for (int i=0; i<24; i++) {
        for (int j=0; j<24; j++) {
            if (game->getBoard()[i][j] == GameCell::WALL)
                spawnables.push_back(Coord { i, j });
        }
    }

    if (spawnables.size() < 2) {
        flagAlive = false;
        pos[0] = Coord { 0, 0 };
        pos[1] = Coord { 0, 0 };
    } else {
        int first = game->getRandomNumber() % spawnables.size();
        int second = first;
        while (first == second)
            second = game->getRandomNumber() % spawnables.size();
        pos[0] = spawnables[first];
        pos[1] = spawnables[second];
    }
}

Gate::~Gate() {
}

bool Gate::tick(Game* game_) {
    assert(game == game_);

    if (!flagAlive)
        return false;
    
    return true;
}

void Gate::draw(Game* game_) {
    assert(game == game_);

    if (!flagAlive)
        return;
    
    for (int i=0; i<2; i++)
        game->getBoard()[pos[i].y][pos[i].x] = GameCell::GATE;
}


int Gate::findIndex(Coord c) {
    if (pos[0].x == c.x && pos[0].y == c.y)
        return 1;
    else
        return 0;
}

Coord Gate::getPos(int idx) {
    return pos[idx];
}

Direction Gate::fixDirection(int idx, Direction dir) {
    Coord c = getPos(idx);

    // 정면
    if (checkNotWall(game, c + dir))
        return dir;
    
    // 시계방향
    dir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
    if (checkNotWall(game, c + dir))
        return dir;
    
    // 시계 반대방향
    dir = static_cast<Direction>((static_cast<int>(dir) + 2) % 4);
    if (checkNotWall(game, c + dir))
        return dir;
    
    // 반대방향
    dir = static_cast<Direction>((static_cast<int>(dir) + 3) % 4);
    if (checkNotWall(game, c + dir))
        return dir;
    
    // 사방이 벽으로 막혀있음
    abort();
}
