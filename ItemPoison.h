#ifndef ITEMPOSION_H_
#define ITEMPOSION_H_

#include "IActor.h"

class ItemPoison : public IActor {
public:
    explicit ItemPoison(Game* game);
    ItemPoison(const ItemPoison& copy) = delete;
    ItemPoison(ItemPoison&& move) = delete;

    ~ItemPoison();

    bool tick(Game* game) override;
    void draw(Game* game) override;

    Coord getPos() const { return pos; }

private:
    Coord pos;
    int remainingTicks;
};

#endif
