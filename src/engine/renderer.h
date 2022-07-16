#pragma once
#include "../glfw/glfw3.h"
#include "../config/options.h"
#include "fps.h"
#include "inputs.h"
#include "state.h"
#include <iostream>


class Renderer {
public:
	Renderer(GameOptions* opts, GLFWwindow* window, GameState* gs);
	void RenderFrame();
	void SetVsync(bool v);

	GLFWwindow* window;

private:
	int rPos =0 , gPos=100, bPos=200;
	int swapInterval = 1;

	FPSCounter fpsCounter;
	GameOptions* opts;
	GameState* gs;
};

