#pragma once
#include <iostream>
#include "glfw3.h"
#include "ui/window.h"
#include "engine/inputs.h"
#include "engine/renderer.h"
#include "engine/state.h"
#include "config/options.h"

class Game {
public:
	int Start(GameOptions args);
};