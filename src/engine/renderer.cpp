#include "renderer.h"
#include <GLES3/gl3.h>
#include <GL/gl.h>

void Renderer::RenderFrame() {
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    auto pos = m_gs.player.GetPosition();

    const GLfloat playerSize = 0.4000;

    glBegin(GL_TRIANGLE_FAN); // Start drawing a line primitive  
    glColor3d(1, 1, 1);
    glVertex2f(0 + pos.x, 0 + pos.y);
    
    glColor3d(0, 1, 0);
    glVertex2f(0 + pos.x, playerSize + pos.y);
    
    glColor3d(1, 0, 0);
    glVertex2f(-playerSize + pos.x, -playerSize + pos.y);
    
    glColor3d(0, 0, 1);
    glVertex2f(playerSize + pos.x, -playerSize + pos.y);
    
    glColor3d(0, 1, 0);
    glVertex2f(0 + pos.x, playerSize + pos.y);
    glEnd();
	
    // UI render
    m_ui.Render();
    m_ui.RenderFPS(fpsCounter);
	
    // pipeline done, swap buffers
	glfwSwapBuffers(m_window);

	// update fps
	fpsCounter.Inc();
}

void Renderer::SetVsync(bool enable) {
	glfwSwapInterval(enable ? 1: 0);
}
