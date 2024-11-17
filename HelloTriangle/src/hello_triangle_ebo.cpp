#include "hello_triangle_ebo.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

HelloTriangleEbo::HelloTriangleEbo() :
    m_VAO{ 0 },
    m_VBO{ 0 },
    m_EBO{ 0 },
    m_shader{ 0 },
    m_window{ nullptr }
{
    const char* vertexShaderSource{ "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0" };

    const char* fragmentShaderSource{ "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0" };

    // First we need to initialize GLFW
    glfwInit();

    // Then, we set configure the window that we will be creating
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates the window
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
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Vertex Shader Object
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the shader source code to the shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment Shader Object
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader Program
    m_shader = glCreateProgram();
    glAttachShader(m_shader, vertexShader);
    glAttachShader(m_shader, fragmentShader);
    glLinkProgram(m_shader);
    glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create and generate VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Create and generate VBO
    glGenBuffers(1, &m_VBO);
    // Bind the newly created VBO to the buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // Copies the previously defined vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and generate EBO
    glGenBuffers(1, &m_EBO);
    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    // Copy the indices into de buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex Data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // We can safely unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void HelloTriangleEbo::Run()
{
    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        // Input
        processInput(m_window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shader);
        glBindVertexArray(m_VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    // de-allocate all resources
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteProgram(m_shader);

    // clear all previously allocated GLFW resources
    glfwTerminate();
}

void HelloTriangleEbo::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void HelloTriangleEbo::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
