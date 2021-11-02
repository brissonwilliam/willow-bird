#include "game.h"

using namespace std;

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

int Game::Start(GameStartArgs args) {
	// init gl
	if (!glfwInit()) {
		std::cout << "Could not init through glfwInit()\n";
		return -1;
	}

	glfwSetErrorCallback(error_callback);

	// init renderer
	Renderer renderer = Renderer();

	// init window
	Window w = Window(renderer);

	int createResult = w.Create(args.width, args.height, "reeeee", WINDOW_WINDOWED);
	if (createResult < 0) {
		return createResult;
	}

	w.StartRenderLoop();
	
	glfwTerminate();

	return 0;
}