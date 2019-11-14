#pragma once
#include "GLM/glm.hpp"
#include <vector>


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "texture.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoords;
};

class Mesh 
{
private:
	VertexArray m_vertexArray;
	VertexBuffer m_vertexBuffer;
	VertexBufferLayout m_layout;
	IndexBuffer m_indexBuffer;

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;

	void SetupMesh();
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
};