#include "game.h"

using namespace std;

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

int Game::Start(GameOptions args) {
	// init gl
	if (!glfwInit()) {
		std::cout << "Could not init through glfwInit()\n";
		return -1;
	}

	// set the error callback
	glfwSetErrorCallback(error_callback);

	// init window
	Window w = Window(&args);
	int createResult = w.Create("my game yahoo!", WINDOW_WINDOWED);
	if (createResult < 0) {
		return createResult;
	}
	auto glWindow = w.glWindow;

	glfwSetKeyCallback(glWindow, InputState::KeyCallback);

	// init renderer and game state
	GameState gs = GameState(glWindow);
	Renderer renderer = Renderer(&args, glWindow, &gs);

	// main game loop
	// inspired by: https://gameprogrammingpatterns.com/game-loop.html
	double lastTime = glfwGetTime();
	double lag = 0.0;
	const double MS_PER_UPDATE = 5.0; // 1frame / 0.005s = 200fps
	while (!glfwWindowShouldClose(glWindow)) {
		double currentTime = glfwGetTime();
		double elapsedTime = currentTime - lastTime;
		lastTime = currentTime;
		lag += elapsedTime;

		// process inputs
		auto actions = InputState::GetAndFlush();
		gs.ProcessInputs(actions);

		// update state and physics with constant time (regardless of framerate)
		// We use fixed timesteps (granular updates) so that we avoid floating point errors: with bigger elapsed time, slower machines would compute less acurately (floating point precision)
		while (lag >= MS_PER_UPDATE) {
			gs.Update();
			lag -= MS_PER_UPDATE;
		}
		// Frame rendering happens arbitrarely, not at a fixed rate. It may be in between 2 cpu game state updates so we need to pass the leftover amount of lag to renderer
		// For example, a 1ms / 5ms per update = 0.2update to do for game state to match the next frame
	    gs.AdjustForNextFrame(lag / MS_PER_UPDATE * 1000);

		// draw the next frame
		renderer.RenderFrame();

		// process events like window moves or resizes. Not required for inputs
		glfwPollEvents();
	}

	// terminate cleanly
	glfwDestroyWindow(w.glWindow);	
	glfwTerminate();

	return 0;
}
