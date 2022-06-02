#ifndef COLORS_H_
#define COLORS_H_

#include <ncurses.h>

enum : short {
    WHITE_ON_BLACK,
    BLACK_ON_WHITE,
    WHITE_ON_BLUE,
    WHITE_ON_MAGENTA,
    WHITE_ON_GREEN,
    WHITE_ON_GRAY,
    WHITE_ON_YELLOW,
    WHITE_ON_ORANGE,
    WHITE_ON_RED,
    MAX_COLOR_PAIRS
};

enum : short {
    COLOR_GRAY = COLOR_CYAN,
    COLOR_ORANGE = 8,
    MAX_COLORS
};

#endif