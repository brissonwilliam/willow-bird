#include "fps.h"

void FPSCounter::Inc() {
	double currentTime = glfwGetTime(); // time in seconds (float)
	frameCount++;

	const float intervalSec = 0.05;
	double secondsSinceLastUpdate = currentTime - this->lastFpsUpdateTime;
	if (secondsSinceLastUpdate >= intervalSec) {
		// tick!, compute fps
		FPSCounter::fps = frameCount / secondsSinceLastUpdate;

		frameCount = 0;
		lastFpsUpdateTime = currentTime;
	}
}

double FPSCounter::GetFPS() {
	return this->fps;
}

double FPSCounter::GetFrameTime() {
	return 1.0 / this->fps;
}
