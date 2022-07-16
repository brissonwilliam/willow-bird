#pragma once
#include <iostream>
#include "glfw3.h"
#include "../config/options.h"

#define WINDOW_WINDOWED NULL

class Window {
public:
	int Create(const char* title, GLFWmonitor* monitor);
	Window(GameOptions* opts);

	GLFWwindow* glWindow;

private:
	GameOptions* gameOpts;
};

