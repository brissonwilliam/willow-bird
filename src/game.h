#pragma once
#include <iostream>
#include "glfw/glfw3.h"
#include "ui/window.h"
#include "engine/renderer.h"


struct GameStartArgs {
	int width, height;
	int monitor;
};

class Game {
public:
	int Start(GameStartArgs args);

private:
	int resX, resY;
};