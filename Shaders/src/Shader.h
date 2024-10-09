#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();
	void setBool(const std::string& uniformName, bool value) const;
	void setInt(const std::string& uniformName, int value) const;
	void setFloat(const std::string& uniformName, float value) const;

private:
	unsigned int m_Id;
};

