#pragma once
#include "../glfw/glfw3.h"
#include <iostream>
#include "../config/options.h"

struct FPSCounter {
public:
	void Inc();
	double GetFPS();
private:
	double lastFpsUpdateTime;
	int frameCount;
	double fps;
};

class Renderer {
public:
	Renderer(GameOptions* opts);
	void SetVsync(bool v);
	void Start(GLFWwindow* window);

private:
	void nextFrame();

	int rPos =0 , gPos=100, bPos=200;
	int swapInterval = 1;

	FPSCounter fpsCounter;
	GameOptions* opts;
	GLFWwindow* window;
};

