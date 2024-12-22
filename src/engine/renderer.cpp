#include "renderer.h"
#include <GLES3/gl3.h>
#include <GL/gl.h>

void initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    // for font text rendering
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
}

Renderer::Renderer(GameOptions* opts, GLFWwindow* window, GameState* gs) {
	m_opts = opts;
	m_window = window;
	m_gs = gs;

	initGL();
	SetVsync(opts->vsync);

    m_txtRenderer.LoadFont("assets/IosevkaCustomMono-Regular.ttf", 48);
}

void Renderer::RenderFrame() {
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    auto pos = m_gs->player.GetPosition();

    const GLfloat playerSize = 0.4000;

//     glBegin(GL_TRIANGLE_FAN); // Start drawing a line primitive  
//         glColor3d(1, 1, 1);
// 		glVertex2f(0 + pos.x, 0 + pos.y);
// 
// 		glColor3d(0, 1, 0);
// 		glVertex2f(0 + pos.x, playerSize + pos.y);
// 
// 		glColor3d(1, 0, 0);
// 		glVertex2f(-playerSize + pos.x, -playerSize + pos.y);
// 
// 		glColor3d(0, 0, 1);
// 		glVertex2f(playerSize + pos.x, -playerSize + pos.y);
// 
// 		glColor3d(0, 1, 0);
// 		glVertex2f(0 + pos.x, playerSize + pos.y);
//     glEnd();
	
    // UI render
    m_txtRenderer.RenderText("caliss ahhhhh!", 25.0f, 25.0f, 0.75, glm::vec3(0.5f, 0.2f, 0.9f));
	
    // pipeline done, swap buffers
	glfwSwapBuffers(this->m_window);

	// update fps
	fpsCounter.Inc();
}

void Renderer::SetVsync(bool enable) {
	glfwSwapInterval(enable ? 1: 0);
}
