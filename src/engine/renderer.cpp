#include "renderer.h"

Renderer::Renderer() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Renderer::render(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.360, 0.933, 0.941, 1.0);
	
	glfwSwapBuffers(window);
	
	// update fps
	fpsCounter.Inc();

	// 
}

void Renderer::SetVsync(bool enable) {
	glfwSwapInterval(enable ? 1: 0);
}

void FPSCounter::Inc() {
	double currentTime = glfwGetTime(); // time in seconds (float)
	frameCount++;

	const float intervalSec = 0.25;
	double secondsSinceLastUpdate = currentTime - lastFpsUpdateTime;
	if (secondsSinceLastUpdate >= intervalSec) {
		double fps = frameCount / secondsSinceLastUpdate;

		std::cout << "\r" << int(fps) << "FPS "<< std::flush;

		frameCount = 0;
		lastFpsUpdateTime = currentTime;
	}
}