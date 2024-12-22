#pragma once
#include "fps.h"
#include "state.h"
#include "text.h"
#include "../config/options.h"


class Renderer {
public:
	Renderer(GameOptions* opts, GLFWwindow* window, GameState* gs);
	void RenderFrame();
	void SetVsync(bool v);

	FPSCounter fpsCounter;

private:
	int rPos =0 , gPos=100, bPos=200;
	int m_swapInterval = 1;

	GameOptions* m_opts;
	GameState* m_gs;
    TextRenderer m_txtRenderer;
	GLFWwindow* m_window;

};

