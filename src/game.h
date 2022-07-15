#pragma once
#include <iostream>
#include "glfw/glfw3.h"
#include "ui/window.h"
#include "engine/inputs.h"
#include "engine/renderer.h"
#include "config/options.h"

class Game {
public:
	int Start(GameOptions args);
};