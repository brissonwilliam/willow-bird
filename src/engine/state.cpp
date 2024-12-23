#include "state.h"
#include <iostream>

GameState::GameState(GLFWwindow* window){
    this->window = window;
    this->player.Load();
    std::cout << "GameState loaded" << std::endl;
}

void GameState::ProcessInputs(std::vector<INPUT_ACTION> inputs) {
    auto playerSpeed = player.att.maxV.x;

    for (int i = 0; i < inputs.size(); i++) {
        switch (inputs.at(i)) {
            case INPUT_ACTION::MOVE_UP:
                player.AddYVelocity(playerSpeed);
                player.upPressed = true;

                break;
            case INPUT_ACTION::MOVE_UP_RELEASE:
                player.upPressed = false;
                if (!player.downPressed) {
                    // instead of Adding the inverse velocity to nullify, avoid precision errors, hard set to 0
                    player.SetYVelocity(0);
                } else {
                    // re-apply the velocity of key being held
                    player.AddYVelocity(-playerSpeed);
                }

                break;
            case INPUT_ACTION::MOVE_DOWN:
                player.AddYVelocity(-playerSpeed);
                player.downPressed = true;

                break;
            case INPUT_ACTION::MOVE_DOWN_RELEASE:
                player.downPressed = false;
                if (!player.upPressed) {
                    // instead of Adding the inverse velocity to nullify, avoid precision errors, hard set to 0
                    player.SetYVelocity(0);
                } else {
                    // re-apply the velocity of key being held
                    player.AddYVelocity(playerSpeed);
                }

                break;
            case INPUT_ACTION::MOVE_RIGHT:
                player.AddXVelocity(playerSpeed);
                player.rightPressed = true;

                break;
            case INPUT_ACTION::MOVE_RIGHT_RELEASE:
                player.rightPressed = false;
                if (!player.leftPressed) {
                    // instead of Adding the inverse velocity to nullify, avoid precision errors, hard set to 0
                    player.SetXVelocity(0);
                } else {
                    // re-apply the velocity of key being held
                    player.AddXVelocity(-playerSpeed);
                }

                break;
            case INPUT_ACTION::MOVE_LEFT:
                player.AddXVelocity(-playerSpeed);
                player.leftPressed = true;

                break;
            case INPUT_ACTION::MOVE_LEFT_RELEASE:
                player.leftPressed = false;
                if (!player.rightPressed) {
                    // instead of Adding the inverse velocity to nullify, avoid precision errors, hard set to 0
                    player.SetXVelocity(0);
                } else {
                    // re-apply the velocity of key being held
                    player.AddXVelocity(playerSpeed);
                }

                break;
            case INPUT_ACTION::QUIT_GAME:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
}

void GameState::Update(double updatePercent) {
    this->player.Update(updatePercent);
}
