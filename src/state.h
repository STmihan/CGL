//
// Created by stmihan on 10/23/2023.
//

#ifndef CGL_STATE_H
#define CGL_STATE_H

#include <vector>
#include "types.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Conway's Game of Life"
#define CANVAS_WIDTH 700
#define CANVAS_HEIGHT 700

namespace CGL {
    struct State {
        std::vector<std::vector<bool>> cells;
        bool autoStep = false;
        int stepInterval = 150;

        int width, height;
        int screenWidth, screenHeight;
        int mouseX, mouseY;
        ivec2 canvasOffset;
    };
}

#endif //CGL_STATE_H
