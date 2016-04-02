#ifndef SHADER_H
#define SHADER_H

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>

// GLEW
#define GLEW_STATIC
#include<GL/glew.h>




class Shader
{
public:

	//Our program id
	GLuint mProgram;


	Shader(const GLchar* vsFilePath, const GLchar* fsFilePath);
	GLuint CompileShader(GLuint shaderType, const GLchar* shaderCode);
	~Shader();

	void use();
private:

};







#endif // !SHADER_H
