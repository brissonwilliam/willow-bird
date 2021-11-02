#include "renderer.h"

Renderer::Renderer() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
}


void Renderer::render(GLFWwindow* window) {
	
	r++;
	if (r > 255) {
		r = 0;
	}

	g++;
	if (g > 255) {
		g = 0;
	}

	b++;
	if (b > 255) {
		b = 0;
	}
	

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	//red to green
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, -1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	// green to blue
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(1.0, -1.0);
	glEnd();

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

		std::cout << "\r" << fps << std::flush;

		frameCount = 0;
		lastFpsUpdateTime = currentTime;
	}
}