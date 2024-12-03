#pragma once
#include <vector>
#include "inputs.h"
#include "../assets/teapot.h"

class GameState {
public:
    GameState(GLFWwindow* window);
    void ProcessInputs(std::vector<INPUT_ACTION> actions);
    void Update();
    void AdjustForNextFrame(double updatePercent);

    GLFWwindow* window;
    Teapot player;

private:
    void update(double multiplier);

    std::vector<INPUT_ACTION> inputs;
};
