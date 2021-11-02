#include "window.h"


Window::Window(Renderer r) {
	renderer = r;
}

// Create sets up a new GLFWwindow
int Window::Create(int width, int height, const char * title, GLFWmonitor* monitor) {	
	this->glWindow = glfwCreateWindow(width, height, title, monitor, NULL);
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
	renderer.SetVsync(true);

	while (!glfwWindowShouldClose(this->glWindow)) {
		renderer.render(glWindow);
		glfwPollEvents();
	}

	/* free the window and context */
	glfwDestroyWindow(this->glWindow);
}