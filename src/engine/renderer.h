#pragma once
#include "../glfw/glfw3.h"
#include "../config/options.h"
#include "./fps.h"
#include "./inputs.h"
#include <iostream>


class Renderer {
public:
	Renderer(GameOptions* opts);
	void SetVsync(bool v);
	void StartGameLoop(GLFWwindow* window);

private:
	void renderFrame();

	int rPos =0 , gPos=100, bPos=200;
	int swapInterval = 1;

	FPSCounter fpsCounter;

	GameOptions* opts;
	GLFWwindow* window;
};

