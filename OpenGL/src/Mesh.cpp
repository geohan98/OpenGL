#include "Mesh.h"
#include "GL/glew.h"

void Mesh::SetupMesh()
{
	m_vertexBuffer = VertexBuffer(&m_vertices[0], m_vertices.size() * sizeof(float));
	m_indexBuffer = IndexBuffer(&m_indices[0], m_indices.size());

	VertexBufferLayout m_layout;
	m_layout.Push<Vertex>(1);
	m_layout.Push<Vertex>(1);
	m_layout.Push<Vertex>(1);

	m_vertexArray.AddBuffer(m_vertexBuffer, m_layout);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;

	SetupMesh();
}

void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
	}
}
