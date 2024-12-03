#pragma once
#include "paths.h"
#include "../engine/asset.h"
#include <GLFW/glfw3.h>

class Teapot : public DynamicAsset {
public:
    void Load() override;
};
