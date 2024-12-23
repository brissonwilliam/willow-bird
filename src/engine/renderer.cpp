#include "renderer.h"
#include <GLES3/gl3.h>
#include <GL/gl.h>

void Renderer::RenderFrame() {
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    auto pos = m_gs.player.GetPosition();

    const GLfloat playerSize = 0.4000;

    m_gs.player.Render();

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

void Renderer::ToggleWireframe() {
    if (isWireframeOn) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
}
