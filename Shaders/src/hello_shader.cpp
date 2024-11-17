#include "hello_shader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

HelloShader::HelloShader() :
    m_VAO{ 0 },
    m_VBO{ 0 },
    m_shader{ nullptr },
    m_window{ nullptr }
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    // Verify if the window has successfully created
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;

        // Terminate GLFW
        glfwTerminate();
    }

    // Make the context of the specified window current
    glfwMakeContextCurrent(m_window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // Set the window resize callback
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    // Sets the triangle vertices coordinates
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    // Create shader
    m_shader = new Shader("shaders/default.vert", "shaders/default.frag");

    // Create and generate VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Create and generate VBO
    glGenBuffers(1, &m_VBO);
    // Bind the newly created VBO to the buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // Copies the previously defined vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color Attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // We can safely unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void HelloShader::Run()
{
    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        // Input
        processInput(m_window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shader->getId());
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    // de-allocate all resources
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteProgram(m_shader->getId());

    // clear all previously allocated GLFW resources
    glfwTerminate();
}

void HelloShader::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void HelloShader::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
