#pragma once
#include "paths.h"
#include "../engine/asset.h"
#include <GLFW/glfw3.h>

class Player : public DynamicAsset {
public:
    Player();
    void Load() override;
    void Update(double elapsed);

    // Used to re-apply velocity when it gets nullified with inputs
    // For example when holding right, pressing left, release left, we still want to move right
    bool rightPressed = false;
    bool leftPressed = false;
    bool upPressed = false;
    bool downPressed = false;

};
