#include "ItemPoison.h"

#include "Game.h"

ItemPoison::ItemPoison(Game* game) {
    pos.y = 0;
    pos.x = 0;
    remainingTicks = 20;

    while (game->getBoard()[pos.y][pos.x] != GameCell::EMPTY) {
        pos.y = game->getRandomNumber() % 24;
        pos.x = game->getRandomNumber() % 24;
    }

    draw(game);
}

ItemPoison::~ItemPoison() {
}

bool ItemPoison::tick(Game* game) {
    return remainingTicks-- > 0;
}

void ItemPoison::draw(Game* game) {
    game->getBoard()[pos.y][pos.x] = GameCell::POISON;
}