#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();
	void setBool(const std::string& uniformName, bool value) const;
	void setInt(const std::string& uniformName, int value) const;
	void setFloat(const std::string& uniformName, float value) const;
	void setMat4(const std::string& uniformName, glm::mat4 value) const;
	void setVec3(const std::string& uniformName, glm::vec3 value) const;

private:
	unsigned int m_Id;
};

