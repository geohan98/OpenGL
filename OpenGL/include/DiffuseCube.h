#pragma once
#include <GLM/glm.hpp>
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

class DiffuseCube
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Color;

	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;

	VertexArray* m_vertexArray;
	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_IndexBuffer;
	VertexBufferLayout* m_Layout;

	Shader* m_Shader;
public:
	DiffuseCube(glm::vec3 position, glm::vec3 scale, glm::vec3 color);
	void Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightPos, glm::vec3 lightColor);
};