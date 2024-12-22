#include "ui.h"
#include "fps.h"

UI::UI(GLFWwindow* window) {
    m_window = window;
    glfwGetWindowSize(window, &m_width, &m_height);

    // setup the projection to use for the text render shaders
    m_projection = glm::ortho(0.0f, float(m_width), 0.0f, float(m_height));

    m_txtRenderer = TextRenderer(m_projection);
    m_txtRenderer.LoadFont("assets/IosevkaCustomMono-Regular.ttf", 48);
}

void UI::Render() {
}

void UI::RenderFPS(FPSCounter& fpsCounter) {

    std::string fpsStr = "fps: " +  std::to_string(int(fpsCounter.GetFPS())) ;
    std::string frameTimeStr = "frameTime(ms): " + std::to_string(int(fpsCounter.GetFrameTimeMS())) ;

    const float x = 25.0f;
    const float y = m_height - 25.0f;

    m_txtRenderer.RenderText(fpsStr, x, y, 0.4, glm::vec3(0.2f, 0.9f, 0.9f));
    m_txtRenderer.RenderText(frameTimeStr, x, y - 25.0f, 0.4, glm::vec3(0.2f, 0.9f, 0.9f));
}

void UI::OnWindowUpdate(int width, int height) {
    m_width = width;
    m_height = height;
}
