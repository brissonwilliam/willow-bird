#pragma once
#include <vector>
#include "inputs.h"
#include "../assets/player.h"

class GameState {
public:
    GameState(GLFWwindow* window);
    void ProcessInputs(std::vector<INPUT_ACTION> actions);
    void Update(double percent=1.0);
    void AdjustForNextFrame(double updatePercent);

    GLFWwindow* window;
    Player player;
};
