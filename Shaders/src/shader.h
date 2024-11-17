#pragma once

typedef unsigned int GLuint;

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    GLuint getId() const;

private:
    GLuint m_id;
};