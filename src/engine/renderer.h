#pragma once
#include "../glfw/glfw3.h"
#include <iostream>

struct FPSCounter {
public:
	void Inc();
private:
	double lastFpsUpdateTime;
	int frameCount;
};

class Renderer {
public:
	Renderer();
	void render(GLFWwindow* window);
	void SetVsync(bool v);
private:
	int r =0 , g=100, b=200;
	int swapInterval = 1;

	FPSCounter fpsCounter;
};

