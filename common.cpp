#include "common.h"

#define IN_RANGE(X, A, B) (X >= A && X <= B)

bool on_screen(int x, int y)
{
    return IN_RANGE(x, 0, TFT_WIDTH) && IN_RANGE(y, 0, TFT_HEIGHT);
}

#undef IN_RANGE
