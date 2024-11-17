#pragma once

// Forward declarations
typedef unsigned int GLuint;
typedef struct GLFWwindow GLFWwindow;

class HelloTriangle
{
public:
    HelloTriangle();
    void Run();

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_shader;
    GLFWwindow* m_window;
};

