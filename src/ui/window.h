#pragma once
#include <iostream>
#include "../glfw/glfw3.h"
#include "../controls/keys.h"
#include "../engine/renderer.h"

#define WINDOW_WINDOWED NULL

class Window {
public:
	int Create(int width, int height, const char* title, GLFWmonitor* monitor);
	void StartRenderLoop();
	Window(Renderer r);

private:
	GLFWwindow* glWindow;
	Renderer renderer;
};

