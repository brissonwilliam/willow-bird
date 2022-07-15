#include "renderer.h"

Renderer::Renderer(GameOptions* opts) {
	this->opts = opts;
}

void initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Renderer::Start(GLFWwindow* window) {
	this->window = window;

	SetVsync(opts->vsync);
	initGL();

	// main game loop
	while (!glfwWindowShouldClose(window)) {
		// inputs are processed by GLFW window, which calls our own callback in inputs.cpp

		//TODO: update(elapsedTime) updates the gamestate with constant time

		renderFrame();

		// TODO: wait for next frame if limited fps

		glfwPollEvents();
	}

}


void Renderer::renderFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.360, 0.933, 0.941, 1.0);
	
	glfwSwapBuffers(this->window);
	
	// update fps
	fpsCounter.Inc();
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
		FPSCounter::fps = frameCount / secondsSinceLastUpdate;

		std::cout << "\r" << int(fps) << "FPS "<< std::flush;

		frameCount = 0;
		lastFpsUpdateTime = currentTime;
	}
}

double FPSCounter::GetFPS() {
	return fps;
}