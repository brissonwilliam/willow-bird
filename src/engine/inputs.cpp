#include "inputs.h"

std::vector<INPUT_ACTION> actions;

void InputState::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				InputState::Push(QUIT_GAME);
				break;
		}
	}

}

void InputState::Push(INPUT_ACTION i) {
	actions.push_back(i);
}

std::vector<INPUT_ACTION> InputState::GetAndFlush() {
	std::vector<INPUT_ACTION> actionsCpy = actions; // vectors make deep copies when using = operator, no need to loop
	actions.clear();
	return actionsCpy;
}