#pragma once
#include <vector>
#include "inputs.h"

class GameState {
public:
    GameState(GLFWwindow* window);
    void ProcessInputs(std::vector<INPUT_ACTION> actions);
    void Update();
    void AdjustForNextFrame(double updatePercent);

    GLFWwindow* window;
private:
    void update(double multiplier = 1.0);
};