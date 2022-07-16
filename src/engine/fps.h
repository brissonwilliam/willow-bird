#pragma once
#include "glfw3.h"
#include <iostream>

struct FPSCounter {
public:
	void Inc();
	double GetFPS();
private:
	double lastFpsUpdateTime;
	int frameCount;
	double fps;
};