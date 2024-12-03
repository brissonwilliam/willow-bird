#include "inputs.h"
#include <queue>

std::queue<INPUT_ACTION> actions;

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
			case GLFW_KEY_ESCAPE:
				InputState::Push(QUIT_GAME);
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
        }

    }

}

void InputState::Push(INPUT_ACTION i) {
	actions.push(i);
}

std::vector<INPUT_ACTION> InputState::GetAndFlush() {
    auto count = actions.size(); // take a snapshot of nb of actions we can read

    std::vector<INPUT_ACTION> ret;
    ret.reserve(count);

    for (int i =0; i < count; i++) {
        ret.push_back(actions.front());
        actions.pop();
    }
	return ret;
}
