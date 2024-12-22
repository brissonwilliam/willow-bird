#pragma once
#include "fps.h"
#include "state.h"
#include "text.h"
#include "ui.h"


class Renderer {
public:
    Renderer(GLFWwindow* window, GameState& gs, UI& ui) :  m_gs(gs), m_ui(ui) {
        m_window = window;
    };
	void RenderFrame();
	void SetVsync(bool v);

	FPSCounter fpsCounter;

private:
	int rPos =0 , gPos=100, bPos=200;
	int m_swapInterval = 1;

	GameState& m_gs;
    TextRenderer m_txtRenderer;
    UI m_ui;
	GLFWwindow* m_window;

};

