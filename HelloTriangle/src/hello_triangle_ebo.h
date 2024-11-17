#pragma once

typedef unsigned int GLuint;
typedef struct GLFWwindow GLFWwindow;

class HelloTriangleEbo
{
public:
    HelloTriangleEbo();
    void Run();

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_shader;
    GLFWwindow* m_window;
};