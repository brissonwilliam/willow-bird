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

		// process inputs. Should be done on every frame, not every state tick
		auto actions = InputState::GetAndFlush();
		gs.ProcessInputs(actions);

        // Update state and physics with constant time (regardless of framerate)
        // We use fixed timesteps (granular updates) so that we avoid floating point errors: with bigger elapsed time, slower machines would compute less acurately (floating point precision)
        while (lag >= MS_PER_UPDATE) {
            gs.Update(1.0);
            lag -= MS_PER_UPDATE;
        }
        // Update a fraction of a normal step for the remaning amount of lag.
        // This is necessary so that when we call Render(), we show the real time frame
        // of the game state. For example, if a bullet or asset collisions would happen in the remaining lag, we need to show it in renderer 
        // Also necessary for when a maching renders super fast, under MS_PER_UPDATE
        auto remainingLagPct = lag / MS_PER_UPDATE;
        gs.Update(1 + remainingLagPct);

		// draw the next frame
		renderer.RenderFrame();

        lag = 0.0;

		// process events like window moves or resizes. Not required for inputs
		glfwPollEvents();
	}

    std::cout << "\nOut of main loop, goodbye!";

	// terminate cleanly
	glfwDestroyWindow(w.glWindow);	
	glfwTerminate();

	return 0;
}
