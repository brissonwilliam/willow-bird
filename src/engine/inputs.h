#pragma once
#include <vector>
#include <GLFW/glfw3.h>

// An INPUT_ACTION represents an actionnable in-game concept. Key binds should trigger those actions.
typedef enum {
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	BOOST,
	QUIT_GAME
} INPUT_ACTION;

class InputState {
public:
	static	void Push(INPUT_ACTION i);
	static std::vector<INPUT_ACTION> GetAndFlush();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


