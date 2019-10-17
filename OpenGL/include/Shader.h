#pragma once

#include <GL/glew.h>

#include <string>

class Shader 
{
private:
	unsigned int m_RendererID;
public:
	Shader();
	~Shader();

	void Bind() const;
	void Unbind() const;

	void AddShader(const std::string& filepath, unsigned int type);
	void ParseShader(const std::string& filepath);

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
};