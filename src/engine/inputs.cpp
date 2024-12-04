#include "inputs.h"
#include <vector>
#include <algorithm>

std::vector<INPUT_ACTION> actions;

void InputState::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_D:
				InputState::Push(MOVE_RIGHT);
				break;
			case GLFW_KEY_A:
				InputState::Push(MOVE_LEFT);
				break;
			case GLFW_KEY_W:
				InputState::Push(MOVE_UP);
				break;
			case GLFW_KEY_S:
				InputState::Push(MOVE_DOWN);
				break;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_D:
				InputState::Push(MOVE_RIGHT_RELEASE);
				break;
			case GLFW_KEY_A:
				InputState::Push(MOVE_LEFT_RELEASE);
				break;
			case GLFW_KEY_W:
				InputState::Push(MOVE_UP_RELEASE);
				break;
			case GLFW_KEY_S:
				InputState::Push(MOVE_DOWN_RELEASE);
				break;
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
    // actions becomes the empty vector, and we return the full actions vector
    auto ret = std::vector<INPUT_ACTION>{};
    actions.swap(ret);

	return ret;
}
