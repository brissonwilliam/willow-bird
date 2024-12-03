#include "state.h"
#include <iostream>

GameState::GameState(GLFWwindow* window){
    this->window = window;
}

void GameState::ProcessInputs(std::vector<INPUT_ACTION> actions) {
    this->inputs = actions;
}

void GameState::Update() {
    update(1.0);
}

void GameState::AdjustForNextFrame(double updatePercent) {
    update(updatePercent);
}

void GameState::update(double multiplier) {
    for (int i = 0; i < this->inputs.size(); i++) {
        switch (this->inputs.at(i)) {
            case INPUT_ACTION::MOVE_RIGHT:
                this->player.SetVelocity(0.01, 0, 0);
                std::cout << "received MOVE_RIGHT\n";
                break;
            case INPUT_ACTION::MOVE_RIGHT_RELEASE:
                this->player.SetVelocity(0.0, 0, 0);
                std::cout << "received MOVE_RIGHT\n";
                break;
            case INPUT_ACTION::MOVE_LEFT:
                this->player.SetVelocity(-0.01, 0, 0);
                std::cout << "received MOVE_LEFT\n";
                break;
            case INPUT_ACTION::MOVE_LEFT_RELEASE:
                this->player.SetVelocity(0.0, 0, 0);
                std::cout << "received MOVE_LEFT_RELEASE\n";
                break;
            case INPUT_ACTION::QUIT_GAME:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
    this->player.Update();
    this->inputs.clear();
}
