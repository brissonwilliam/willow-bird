#include "renderer.h"

void initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Renderer::Renderer(GameOptions* opts, GLFWwindow* window, GameState* gs) {
	this->opts = opts;
	this->window = window;
	this->gs = gs;

	initGL();
	SetVsync(opts->vsync);
}

void Renderer::RenderFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.360, 0.933, 0.941, 1.0);
	
	glfwSwapBuffers(this->window);
	
	// update fps
	fpsCounter.Inc();
}

void Renderer::SetVsync(bool enable) {
	glfwSwapInterval(enable ? 1: 0);
}