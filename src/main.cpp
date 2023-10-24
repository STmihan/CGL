#include <thread>
#include "state.h"
#include "game.h"
#include "size_utils.h"
#include "Sime.h"


class Sandbox : public Sime::Application {
public:
    CGL::State state{};
    std::chrono::high_resolution_clock::time_point lastStep = std::chrono::high_resolution_clock::now();


    Sandbox() {
        CGL::resize(&state, 100, 100);
        CGL::generateGridWithRandomNumbers(&state, 0.5f);
    }

    ~Sandbox() override = default;

public:
    void init() override {
        SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &state.screenWidth, &state.screenHeight);
    }

    void draw(SDL_Renderer *renderer) override {
        SDL_GetMouseState(&state.mouseX, &state.mouseY);
        CGL::draw(&state, renderer);

        if (state.autoStep) {
            auto now = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastStep).count() > state.stepInterval) {
                CGL::step(&state);
                lastStep = now;
            }
        }
        int mouseX, mouseY;
        if (SDL_GetMouseState(&mouseX, &mouseY)&SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (CGL::inBounds(&state, mouseX, mouseY)) {
                ivec2 cell = CGL::toCellCoordinates(&state, {mouseX, mouseY});
                    CGL::setCell(&state, cell.x, cell.y, true);
            }
        } else if (SDL_GetMouseState(&mouseX, &mouseY)&SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            if (CGL::inBounds(&state, mouseX, mouseY)) {
                ivec2 cell = CGL::toCellCoordinates(&state, {mouseX, mouseY});
                CGL::setCell(&state, cell.x, cell.y, false);
            }
        }
    }

    void drawUI(ImGuiIO &io) override {
        ImGui::Begin("Game of Life");
        {
            ImGui::Text("Mouse: %d, %d", state.mouseX, state.mouseY);
            if (ImGui::Button("Step")) {
                CGL::step(&state);
            }

            ImGui::Checkbox("Auto Step", &state.autoStep);
            ImGui::InputInt("Step Interval (ms)", &state.stepInterval, 10, 1000);

            if (ImGui::Button("Clear")) {
                CGL::clear(&state);
            }
            if (ImGui::Button("Random")) {
                CGL::generateGridWithRandomNumbers(&state, 0.5f);
            }
            if (ImGui::InputInt("Width", &state.width, 1, 1000)) {
                CGL::resize(&state, state.width, state.height);
            }
            if (ImGui::InputInt("Height", &state.height, 1, 1000)) {
                CGL::resize(&state, state.width, state.height);
            }
            ImGui::Text("Cell Count: %d", state.width * state.height);
            ImGui::Text("FPS: %f", io.Framerate);
            const ivec2 &cell = CGL::toCellCoordinates(&state, {state.mouseX, state.mouseY});
            ImGui::Text("Current Cell: %d, %d", cell.x, cell.y);

            auto size = ImGui::GetWindowSize();
            state.canvasOffset = {std::floor(size.x), 0};
        }
        ImGui::End();
    }

    void processEvents(const SDL_Event *event) override {
        if (event->button.state == SDL_PRESSED) {

        }
        if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
            SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &state.screenWidth, &state.screenHeight);
        }
    }
};

int main(int argc, char **argv) {
    auto *app = new Sandbox();
    return Sime::entryPoint(app, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
}
