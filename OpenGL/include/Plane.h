#pragma once
#include <vector>
#include <string>
#include "GLM/glm.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "texture.h"

class Plane
{
private:
	std::vector <float> m_Vertices;
	std::vector <unsigned int> m_Indices;

	VertexArray* vao;
	VertexBuffer* vbo;
	VertexBufferLayout* vbl;
	IndexBuffer* ibo;
	Shader* shader;
	Texture* m_diffuse;
	Texture* m_normal;
	Texture* m_displacement;
public:
	Plane(glm::vec3 position, std::string vertex, std::string frag, std::string diffuse = "NULL", std::string normal = "NULL", std::string height = "NULL");
	void Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 lightPos);
};