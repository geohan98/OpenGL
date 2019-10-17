#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader()
{
	m_RendererID = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::AddShader(const std::string & filepath, unsigned int type)
{
	unsigned int shader = CompileShader(type, nullptr);
	glAttachShader(m_RendererID, shader);
	glDeleteShader(shader);
}

void Shader::ParseShader(const std::string & filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];

	while (std::getline(stream, line));
	{
	}
}

unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string & fragShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	m_RendererID = program;
	return 0;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string & source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, msg);
		std::cout << "Failed To Compile " <<  (type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << " shader!"<< std::endl;
		std::cout << msg << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
