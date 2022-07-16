#include "fps.h"

void FPSCounter::Inc() {
	double currentTime = glfwGetTime(); // time in seconds (float)
	frameCount++;

	const float intervalSec = 0.25;
	double secondsSinceLastUpdate = currentTime - lastFpsUpdateTime;
	if (secondsSinceLastUpdate >= intervalSec) {
		// tick!, compute fps
		FPSCounter::fps = frameCount / secondsSinceLastUpdate;

		std::cout << "\r" << int(fps) << "FPS "<< std::flush;

		frameCount = 0;
		lastFpsUpdateTime = currentTime;
	}
}

double FPSCounter::GetFPS() {
	return fps;
}