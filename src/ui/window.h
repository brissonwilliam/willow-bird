#pragma once
#include <iostream>
#include "../glfw/glfw3.h"
#include "../controls/keys.h"
#include "../engine/renderer.h"
#include "../config/options.h"

#define WINDOW_WINDOWED NULL

class Window {
public:
	int Create(const char* title, GLFWmonitor* monitor);
	void StartRenderLoop();
	Window(Renderer* r, GameOptions* opts);

private:
	GLFWwindow* glWindow;
	Renderer* renderer;
	GameOptions* gameOpts;
};

