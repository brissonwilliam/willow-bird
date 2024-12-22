#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

struct FPSCounter {
public:
	void Inc();
	double GetFPS();
	double GetFrameTimeMS();
private:
	double lastFpsUpdateTime;
	int frameCount;
	double fps;
};
