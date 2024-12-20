#pragma once
#include <GLFW/glfw3.h>
#include "../config/options.h"
#include "fps.h"
#include "state.h"
#include <iostream>


class Renderer {
public:
	Renderer(GameOptions* opts, GLFWwindow* window, GameState* gs);
	void RenderFrame();
	void SetVsync(bool v);

	GLFWwindow* window;

	FPSCounter fpsCounter;

private:
	int rPos =0 , gPos=100, bPos=200;
	int swapInterval = 1;

	GameOptions* opts;
	GameState* gs;
};

