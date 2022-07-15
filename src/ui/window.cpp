#include "window.h"

Window::Window(GameOptions* opts) {
	gameOpts = opts;
}

// Create sets up a new GLFWwindow
int Window::Create(const char * title, GLFWmonitor* monitor) {	
	this->glWindow = glfwCreateWindow(gameOpts->width, gameOpts->height, title, monitor, NULL);
	if (glWindow == NULL) {
		std::cout << "Could not init window\n";
		return -1;
	}
	glfwMakeContextCurrent(glWindow);

	return 0;
}