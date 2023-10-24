//
// Created by stmihan on 10/24/2023.
//

#include "size_utils.h"

namespace CGL {
    bool inBounds(State *state, int x, int y) {
        int screenWidth, screenHeight;
        SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &screenWidth, &screenHeight);
        ivec2 screen = {screenWidth - state->canvasOffset.x, screenHeight - state->canvasOffset.y};
        int startX = state->canvasOffset.x + (screen.x - CANVAS_WIDTH) / 2;
        int startY = state->canvasOffset.y + (screen.y - CANVAS_HEIGHT) / 2;
        bool a = x >= startX;
        bool a1 = x <= startX + CANVAS_WIDTH;
        bool b = y >= startY;
        bool b1 = y <= startY + CANVAS_HEIGHT;
        return a && a1 && b && b1;
    }

    ivec2 toCellCoordinates(State *state, ivec2 mouse) {
        float cellWidth = (float) CANVAS_WIDTH / (float) state->width;
        float cellHeight = (float) CANVAS_HEIGHT / (float) state->height;
        int screenWidth, screenHeight;
        SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &screenWidth, &screenHeight);
        ivec2 screen = {screenWidth - state->canvasOffset.x, screenHeight - state->canvasOffset.y};
        float startX = (float) state->canvasOffset.x + ((float) screen.x - (float)CANVAS_WIDTH) / 2;
        float startY = (float) state->canvasOffset.y + ((float) screen.y - (float) CANVAS_HEIGHT) / 2;

        int x = std::floor(((float) mouse.x - startX) / cellWidth);
        int y = std::floor(((float) mouse.y - startY) / cellHeight);

        return {x, y};
    }

    ivec2 toScreenCoordinates(State *state, ivec2 cell) {
        float cellWidth = (float) CANVAS_WIDTH / (float) state->width;
        float cellHeight = (float) CANVAS_HEIGHT / (float) state->height;
        int screenWidth, screenHeight;
        SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &screenWidth, &screenHeight);
        ivec2 screen = {screenWidth - state->canvasOffset.x, screenHeight - state->canvasOffset.y};
        float startX = (float) state->canvasOffset.x + ((float) screen.x - (float)CANVAS_WIDTH) / 2;
        float startY = (float) state->canvasOffset.y + ((float) screen.y - (float) CANVAS_HEIGHT) / 2;

        int x = std::floor(startX + (float) cell.x * cellWidth);
        int y = std::floor(startY + (float) cell.y * cellHeight);

        return {x, y};
    }
}
