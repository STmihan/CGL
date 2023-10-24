//
// Created by stmihan on 10/23/2023.
//

#ifndef CGL_GAME_H
#define CGL_GAME_H

#include <SDL.h>
#include "state.h"
#include "types.h"

namespace CGL {
    void resize(State *state, int width, int height);
    void generateGridWithRandomNumbers(State *state, float fillPercentage);
    void step(State *state);
    void setCell(State *state, int x, int y, bool value);
    void draw(State *state, SDL_Renderer *renderer);
    void clear(State *state);
}
#endif //CGL_GAME_H
