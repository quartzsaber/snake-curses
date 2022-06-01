#include "Snake.h"

#include "Game.h"

Snake::Snake(Game* game) : dir(Direction::LEFT) {
    pos.x = 13;
    pos.y = 13;
    for (int i=1; i<=3; i++)
        trail.push_back(Coord { pos.y, pos.x + i });
}

Snake::~Snake() {
}

bool Snake::tick(Game* game) {
    static const Coord delta[4] = {
        { -1,  0 },
        {  0,  1 },
        {  1,  0 },
        {  0, -1 },
    };

    Board& board = game->getBoard();

    trail.pop_back();
    trail.push_front(pos);

    const Coord& movement = delta[static_cast<int>(dir)];
    pos.y += movement.y;
    pos.x += movement.x;

    if (board[pos.y][pos.x] != GameCell::EMPTY)
        return false;

    return true;
}

void Snake::draw(Game* game) {
    Board& board = game->getBoard();
    board[pos.y][pos.x] = GameCell::SNAKE_HEAD;

    for (const Coord& co : trail) {
        board[co.y][co.x] = GameCell::SNAKE_TRAIL;
    }
}