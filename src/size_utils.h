//
// Created by stmihan on 10/24/2023.
//

#ifndef CGL_SIZE_UTILS_H
#define CGL_SIZE_UTILS_H

#include <cmath>
#include "state.h"
#include "game.h"

namespace CGL {
    bool inBounds(State *state, int x, int y);

    ivec2 toCellCoordinates(State *state, ivec2 mouse);

    ivec2 toScreenCoordinates(State *state, ivec2 cell);
}

#endif //CGL_SIZE_UTILS_H
