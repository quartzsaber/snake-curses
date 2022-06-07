#include "Snake.h"

#include "Game.h"
#include "ItemGrowth.h"
#include "ItemPoison.h"
#include "Gate.h"

Snake::Snake(Game* game) : flagAlive(true), dir(Direction::LEFT) {
    pos.x = 13;
    pos.y = 13;
    for (int i=1; i<=3; i++)
        trail.push_back(Coord { pos.y, pos.x + i });
}

Snake::~Snake() {
}

bool Snake::tick(Game* game) {
    Board& board = game->getBoard();

    trail.push_front(pos);
    pos += dir;

    switch (board[pos.y][pos.x]) {
    case GameCell::EMPTY:
        trail.pop_back();
        break;
    case GameCell::GROWTH:
        game->filterActor([this](const std::shared_ptr<IActor>& p) -> bool {
            ItemGrowth* ptr = dynamic_cast<ItemGrowth*>(p.get());
            return (ptr == nullptr) || (ptr->getPos().x != pos.x || ptr->getPos().y != pos.y);
        });
        break;
    case GameCell::POISON:
        trail.pop_back();
        trail.pop_back();
        game->filterActor([this](const std::shared_ptr<IActor>& p) -> bool {
            ItemPoison* ptr = dynamic_cast<ItemPoison*>(p.get());
            return (ptr == nullptr) || (ptr->getPos().x != pos.x || ptr->getPos().y != pos.y);
        });
        break;
    case GameCell::GATE: {
        trail.pop_back();
        std::shared_ptr<IActor> ptr = game->findActor([this](const std::shared_ptr<IActor>& ptr) -> bool {
            return dynamic_cast<Gate*>(ptr.get()) != nullptr;
        });
        Gate* p = dynamic_cast<Gate*>(ptr.get());
        if (p == nullptr)
            break;
        int idx = p->findIndex(pos);
        int dst = (idx + 1) % 2;
        dir = p->fixDirection(idx, dir);
        pos = p->getPos(idx) + dir;
        break;
    }
    default:
        flagAlive = false;
    }

    return flagAlive;
}

void Snake::draw(Game* game) {
    Board& board = game->getBoard();
    board[pos.y][pos.x] = GameCell::SNAKE_HEAD;

    for (const Coord& co : trail) {
        board[co.y][co.x] = GameCell::SNAKE_TRAIL;
    }
}