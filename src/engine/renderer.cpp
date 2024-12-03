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

    glBegin(GL_QUADS); // Start drawing a line primitive  
    auto pos = gs->player.GetPosition();
    glVertex2f(-0.5f + pos.x, -0.5f + pos.y); // The bottom left corner  
    glVertex2f(-0.5f + pos.x, 0.5f + pos.y); // The top left corner  
    glVertex2f(0.5f + pos.x, 0.5f + pos.y); // The top right corner  
    glVertex2f(0.5f + pos.x, -0.5f + pos.y); // The bottom right corner
    glEnd();
	
	
	glfwSwapBuffers(this->window);

	// update fps
	fpsCounter.Inc();
}

void Renderer::SetVsync(bool enable) {
	glfwSwapInterval(enable ? 1: 0);
}
