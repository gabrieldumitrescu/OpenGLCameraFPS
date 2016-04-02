/* Shader class impl*/

#include "Shader.h"

Shader::Shader(const GLchar* vsFilePath, const GLchar* fsFilePath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vsFilePath);
		fShaderFile.open(fsFilePath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into GLchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	GLuint vertex = CompileShader(GL_VERTEX_SHADER, vShaderCode);
	GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fShaderCode);

	GLint success;
	GLchar infoLog[512];


	this->mProgram = glCreateProgram();
	glAttachShader(this->mProgram, vertex);
	glAttachShader(this->mProgram, fragment);
	glLinkProgram(this->mProgram);
	// Print linking errors if any
	glGetProgramiv(this->mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->mProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);


}


GLuint Shader::CompileShader(GLuint shaderType, const GLchar* shaderCode)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << shaderCode << std::endl;
	}
	return shader;
}
Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(mProgram);
}