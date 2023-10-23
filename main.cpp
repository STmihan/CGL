#include "Sime.h"

class Sandbox : public Sime::Application {
public:
    Sandbox() = default;
    ~Sandbox() override = default;

protected:
    void processEvents(const SDL_Event *event) override {

    }

    void draw(SDL_Renderer *renderer) override {
        const SDL_Rect rect = {0, 0, 200, 200};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    void drawUI(ImGuiIO &io) override {
        ImGui::ShowDemoWindow();
    }
};

int main(int argc, char ** argv) {
    auto *app = new Sandbox();
    return Sime::entryPoint(app);
}
