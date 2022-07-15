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

void Renderer::StartGameLoop(GLFWwindow* window) {
	this->window = window;

	SetVsync(opts->vsync);

	initGL();

	// main game loop
	while (!glfwWindowShouldClose(window)) {
		auto actions = InputState::GetAndFlush();

		// TODO: send inputs to game state instead
		// process input actions
		for (int i = 0; i < actions.size(); i++) {
			switch (actions.at(i)) {
				case INPUT_ACTION::QUIT_GAME:
					glfwSetWindowShouldClose(window, GLFW_TRUE);
					break;
			}
		}

		//TODO: update(elapsedTime) updates the gamestate with constant time. 
		// Make sure to limit elapsed time to not cause glitches (if game doesn't respond for 1 second for example)

		renderFrame();

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