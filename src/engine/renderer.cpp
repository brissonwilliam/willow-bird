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
}

void Renderer::SetVsync(bool enable) {
	#ifdef _WIN32
		glfwSwapInterval(enable ? 1: 0);
	#endif
	
}

void FPSCounter::Inc() {
	double currentTime = glfwGetTime();
	frameCount++;

	const float intervalSec = 0.25;
	double delta = currentTime - lastFpsUpdateTime;
	if (delta >= intervalSec)
	{
		int fps = frameCount / delta;

		std::cout << "\r" << fps << "FPS "<< std::flush;

		frameCount = 0;
		lastFpsUpdateTime = currentTime;
	}
}