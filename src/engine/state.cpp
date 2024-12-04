#include "state.h"
#include <iostream>

GameState::GameState(GLFWwindow* window){
    this->window = window;
}

void GameState::ProcessInputs(std::vector<INPUT_ACTION> inputs) {
    auto playerVelX = player.att.maxV.x;

    for (int i = 0; i < inputs.size(); i++) {
        switch (inputs.at(i)) {
            case INPUT_ACTION::MOVE_RIGHT:
                std::cout << "received MOVE_RIGHT\n";

                player.AddXVelocity(player.att.maxV.x);
                player.rightPressed = true;
                break;
            case INPUT_ACTION::MOVE_RIGHT_RELEASE:
                std::cout << "received MOVE_RIGHT\n";

                player.rightPressed = false;
                if (!player.leftPressed) {
                    // instead of Adding the inverse velocity to nullify, avoid precision errors, hard set to 0
                    player.SetXVelocity(0);
                } else {
                    // re-apply the velocity of key being held
                    player.SetXVelocity(-playerVelX);
                }
                break;
            case INPUT_ACTION::MOVE_LEFT:
                std::cout << "received MOVE_LEFT\n";

                player.AddXVelocity(-playerVelX);
                player.leftPressed = true;
                break;
            case INPUT_ACTION::MOVE_LEFT_RELEASE:
                std::cout << "received MOVE_LEFT_RELEASE\n";

                player.leftPressed = false;
                if (!player.rightPressed) {
                    // instead of Adding the inverse velocity to nullify, avoid precision errors, hard set to 0
                    player.SetXVelocity(0);
                } else {
                    // re-apply the velocity of key being held
                    player.SetXVelocity(playerVelX);
                }
                break;
            case INPUT_ACTION::QUIT_GAME:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
}

void GameState::Update(double updatePercent) {
    this->player.Update();
}
