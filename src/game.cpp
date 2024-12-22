#include "game.h"
#include <cmath>

using namespace std;

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    // for font text rendering
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
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
    // GLFWmonitor* fullscreenWindow = glfwGetPrimaryMonitor();
    GLFWmonitor* windowType = NULL;
    const char* title = "my game yahoo!";
	GLFWwindow* glWindow = glfwCreateWindow(args.width, args.height, title, windowType, NULL);
	if (glWindow == NULL) {
		std::cout << "Could not init window\n";
		return -1;
	}
	glfwMakeContextCurrent(glWindow);

	glfwSetKeyCallback(glWindow, InputState::KeyCallback);

	// init renderer and game state
    initGL();

	GameState gs = GameState(glWindow);

    UI ui = UI(glWindow);

	Renderer renderer = Renderer(glWindow, gs, ui);
    renderer.SetVsync(args.vsync);

	// main game loop
	// inspired by: https://gameprogrammingpatterns.com/game-loop.html
	double lastTime = glfwGetTime() * 1000;
	double lag = 0.0;
	const double targetTickRateMS = 16; // ~60fps (1/60 = 16.6667). Unit of time representing 1 tick aka Update(1)
	while (!glfwWindowShouldClose(glWindow)) {
		double currentTime = glfwGetTime() * 1000;
		double elapsedTime = currentTime - lastTime;
		lastTime = currentTime;
		lag += elapsedTime;

		// process inputs. Should be done on every frame, not every state tick
		auto actions = InputState::GetAndFlush();
		gs.ProcessInputs(actions);

        // Update state and physics with constant time (regardless of framerate)
        // We use fixed timesteps (granular updates) so that we avoid floating point errors: with bigger elapsed time, slower machines would compute less acurately (floating point precision)
        while (lag >= targetTickRateMS) {
            gs.Update();
            lag -= targetTickRateMS;
        }
        // Update a fraction of a normal step for the remaning amount of lag.
        // This is necessary so that when we call Render(), we show the real time frame
        // of the game state. For example, if a bullet or asset collisions would happen in the remaining lag, we need to show it in renderer 
        // Also necessary for when a maching renders super fast, where initial lag is under target tick rate. At least 1 tick is done
        auto remainingLagPct = lag / targetTickRateMS;
        gs.Update(remainingLagPct);

        lag = 0.0;

		// draw the next frame
		renderer.RenderFrame();

		// process events like window moves or resizes. Not required for inputs
		glfwPollEvents();

        // "sleep" when fps goes vroom vroom
        /*
        double frameTimeMs = glfwGetTime() * 1000 - currentTime;
        double fps =  1.0 / (frameTimeMs / 1000);
        */

        const double maxFpsCap = 500.0;
	}

    std::cout << "\nOut of main loop, goodbye!";

	// terminate cleanly
	glfwDestroyWindow(glWindow);	
	glfwTerminate();

	return 0;
}
