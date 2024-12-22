#pragma once
#include <GLFW/glfw3.h>
#include "engine/renderer.h"
#include "engine/state.h"
#include "config/options.h"

class Game {
public:
	int Start(GameOptions args);
};
