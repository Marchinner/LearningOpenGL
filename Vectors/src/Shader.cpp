#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) :
	m_Id{ glCreateProgram()}
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertexShaderFile.open(vertexPath);
		std::stringstream vertexShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();
		vertexCode = vertexShaderStream.str();

		fragmentShaderFile.open(fragmentPath);
		std::stringstream fragmentShaderStream;
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		fragmentShaderFile.close();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	// Vertex shader
	unsigned int vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512]{ };
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Shader program
	glAttachShader(m_Id, vertexShader);
	glAttachShader(m_Id, fragmentShader);
	glLinkProgram(m_Id);
	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_Id, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::use()
{
	glUseProgram(m_Id);
}

void Shader::setBool(const std::string& uniformName, bool value) const
{
	glUniform1i(glGetUniformLocation(m_Id, uniformName.c_str()), (int)value);
}

void Shader::setInt(const std::string& uniformName, int value) const
{
	glUniform1i(glGetUniformLocation(m_Id, uniformName.c_str()), value);
}

void Shader::setFloat(const std::string& uniformName, float value) const
{
	glUniform1f(glGetUniformLocation(m_Id, uniformName.c_str()), value);
}

void Shader::setMat4(const std::string& uniformName, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_Id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
