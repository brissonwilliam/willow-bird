#include "state.h"

GameState::GameState(GLFWwindow* window){
    this->window = window;
}

void GameState::ProcessInputs(std::vector<INPUT_ACTION> actions) {
    for (int i = 0; i < actions.size(); i++) {
        switch (actions.at(i)) {
            case INPUT_ACTION::QUIT_GAME:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
}

void GameState::Update() {
    update(1.0);
}

void GameState::AdjustForNextFrame(double updatePercent) {
    update(updatePercent);
}

void GameState::update(double multiplier) {

}