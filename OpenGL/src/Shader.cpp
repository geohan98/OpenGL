#include "Shader.h"

#include <iostream>
#include <fstream>

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
	{
		std::cout << "Uniform " << name << " Does not exist" << std::endl;
	}

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
	glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}

void Shader::setUniform3f(const std::string& name, float f1, float f2, float f3)
{
	glUniform3f(GetUniformLocation(name), f1, f2, f3);
}

Shader::Shader(const std::string& vertexShader, const std::string& fragShader)
{
	m_RendererID = CreateShader(vertexShader, fragShader);
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

std::string Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	std::string content;
	content.assign((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));

	return content;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, ParseShader(vertexShader));
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, ParseShader(fragShader));

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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
		char* msg = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, msg);
		std::cout << "Failed To Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << " shader!" << std::endl;
		std::cout << msg << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
