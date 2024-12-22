#pragma once
#include "fps.h"
#include "text.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class UI {
    public:
        UI(GLFWwindow* window);
        void Render();
        void RenderFPS(FPSCounter& fpsCounter);
        void OnWindowUpdate(int width, int height);
        void SetFpsCounter(FPSCounter& fps);

    private:
        GLFWwindow* m_window;
        TextRenderer m_txtRenderer;
        glm::mat4 m_projection;
        int m_width; 
        int m_height;
};
