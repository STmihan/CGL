//
// Created by stmihan on 10/23/2023.
//

#include "game.h"
#include <cmath>
#include <random>
#include "size_utils.h"

#define BACKGROUND_COLOR 0xD0CCD0FF
#define CELL_COLOR 0x000000FF

#define HEX_COLOR(hex)                      \
    ((hex) >> (3 * 8)) & 0xFF,              \
    ((hex) >> (2 * 8)) & 0xFF,              \
    ((hex) >> (1 * 8)) & 0xFF,              \
    ((hex) >> (0 * 8)) & 0xFF

int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void drawCell(CGL::State *state, SDL_Renderer *renderer, int x, int y) {
    int cellWidth = CANVAS_WIDTH / state->width;
    int cellHeight = CANVAS_HEIGHT / state->height;

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    SDL_Rect rect{};
    rect.x = CGL::toScreenCoordinates(state, {x, y}).x;
    rect.y = CGL::toScreenCoordinates(state, {x, y}).y;
    rect.w = cellWidth;
    rect.h = cellHeight;

    SDL_RenderFillRect(renderer, &rect);
}

namespace CGL {
    void resize(State *state, int width, int height) {
        state->width = width;
        state->height = height;

        state->cells.resize(width);
        for (int i = 0; i < width; i++) {
            state->cells[i].resize(height);
        }
    }

    void generateGridWithRandomNumbers(State *state, float fillPercentage) {
        clear(state);
        int fillCount = (int) std::floor((float) (state->width * state->height) * fillPercentage);

        for (int i = 0; i < fillCount; i++) {
            int x = randomInt(0, state->width - 1);
            int y = randomInt(0, state->height - 1);
            state->cells[x][y] = true;
        }
    }


    void step(State *state) {
        std::vector<std::vector<bool>> newCells;
        newCells.resize(state->width);
        for (int i = 0; i < state->width; i++) {
            newCells[i].resize(state->height);
        }

        for (int x = 0; x < state->width; ++x) {
            for (int y = 0; y < state->height; ++y) {
                int neighbors = 0;
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (i == 0 && j == 0) continue;
                        int nx = x + i;
                        int ny = y + j;
                        if (nx >= 0 && nx < state->width && ny >= 0 && ny < state->height) {
                            if (state->cells[nx][ny]) {
                                neighbors++;
                            }
                        }
                    }
                }

                if (state->cells[x][y]) {
                    if (neighbors == 2 || neighbors == 3) {
                        newCells[x][y] = true;
                    } else {
                        newCells[x][y] = false;
                    }
                } else {
                    if (neighbors == 3) {
                        newCells[x][y] = true;
                    } else {
                        newCells[x][y] = false;
                    }
                }
            }
        }

        state->cells = newCells;
    }

    void setCell(State *state, int x, int y, bool value) {
        state->cells[x][y] = value;
    }

    void draw(State *state, SDL_Renderer *renderer) {
        SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR));
        SDL_Rect bg = {0, 0, state->screenWidth, state->screenHeight};
        SDL_RenderFillRect(renderer, &bg);

        SDL_SetRenderDrawColor(renderer, HEX_COLOR(CELL_COLOR));
        for (int x = 0; x < state->width; x++) {
            for (int y = 0; y < state->height; y++) {
                if (state->cells[x][y]) {
                    drawCell(state, renderer, x, y);
                }
            }
        }
    }

    void clear(State *state) {
        for (int x = 0; x < state->width; x++) {
            for (int y = 0; y < state->height; y++) {
                state->cells[x][y] = false;
            }
        }
    }
}
