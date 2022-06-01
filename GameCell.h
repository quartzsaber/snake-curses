#ifndef GAME_CELL_H_
#define GAME_CELL_H_

enum class GameCell : unsigned char {
	UNKNOWN = 0,
	GROWTH,
	POISON,
	PORTAL,
    IMMUNE_WALL,
	WALL,
	SNAKE_HEAD,
	SNAKE_TRAIL,
	EMPTY
};

using Board = GameCell[24][24];

#endif
