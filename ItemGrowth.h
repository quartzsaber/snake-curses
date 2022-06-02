#ifndef ITEMGROWTH_H_
#define ITEMGROWTH_H_

#include "IActor.h"

class ItemGrowth : public IActor {
public:
    explicit ItemGrowth(Game* game);
    ItemGrowth(const ItemGrowth& copy) = delete;
    ItemGrowth(ItemGrowth&& move) = delete;

    ~ItemGrowth();

    bool tick(Game* game) override;
    void draw(Game* game) override;

    Coord getPos() const { return pos; }

private:
    Coord pos;
    int remainingTicks;
};

#endif
