#include "window.h"

Window::Window(Renderer* r, GameOptions* opts) {
	renderer = r;
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
	glfwSetKeyCallback(glWindow, Keys::keyCallback);

	return 0;
}

// StartRenderLoop calls the renderer in a loop. This a blocking call.
// Ends when glfwWindowShouldClose() is called.
void Window::StartRenderLoop() {
	renderer->SetVsync(gameOpts->vsync);

	while (!glfwWindowShouldClose(this->glWindow)) {
		renderer->render(glWindow);
		glfwPollEvents();
	}

	/* free the window and context */
	glfwDestroyWindow(this->glWindow);
}