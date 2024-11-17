#pragma once
#include "shader.h"

typedef unsigned int GLuint;
typedef struct GLFWwindow GLFWwindow;

class HelloShader
{
public:
    HelloShader();
    void Run();

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

private:
    GLuint m_VAO;
    GLuint m_VBO;
    Shader* m_shader;
    GLFWwindow* m_window;
};

