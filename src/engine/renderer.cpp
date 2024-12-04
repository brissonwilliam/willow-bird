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
	glClearColor(0.1, 0.1, 0.1, 1.0);

    auto pos = gs->player.GetPosition();

    const GLfloat playerSize = 0.4000;
    glBegin(GL_TRIANGLE_FAN); // Start drawing a line primitive  
        glColor3d(1, 1, 1);
		glVertex2f(0 + pos.x, 0 + pos.y);

		glColor3d(0, 1, 0);
		glVertex2f(0 + pos.x, playerSize + pos.y);

		glColor3d(1, 0, 0);
		glVertex2f(-playerSize + pos.x, -playerSize + pos.y);

		glColor3d(0, 0, 1);
		glVertex2f(playerSize + pos.x, -playerSize + pos.y);

		glColor3d(0, 1, 0);
		glVertex2f(0 + pos.x, playerSize + pos.y);
    glEnd();
	
	
	glfwSwapBuffers(this->window);

	// update fps
	fpsCounter.Inc();
}

void Renderer::SetVsync(bool enable) {
	glfwSwapInterval(enable ? 1: 0);
}
