#include "ItemGrowth.h"

#include "Game.h"

ItemGrowth::ItemGrowth(Game* game) {
    pos.y = 0;
    pos.x = 0;
    remainingTicks = 20;

    while (game->getBoard()[pos.y][pos.x] != GameCell::EMPTY) {
        pos.y = game->getRandomNumber() % 24;
        pos.x = game->getRandomNumber() % 24;
    }

    draw(game);
}

ItemGrowth::~ItemGrowth() {
}

bool ItemGrowth::tick(Game* game) {
    return remainingTicks-- > 0;
}

void ItemGrowth::draw(Game* game) {
    game->getBoard()[pos.y][pos.x] = GameCell::GROWTH;
}