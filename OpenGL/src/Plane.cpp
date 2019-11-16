#include "Plane.h"
#include <GL/glew.h>



Plane::Plane(glm::vec3 position, glm::vec3 scale, glm::vec3 color)
{
	m_Position = position;
	m_Scale = scale;
	m_Color = color;

	m_Vertices = {
			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f, 0.5f,  0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
	};

	m_Indices = {
			2, 1, 0,
			0, 3, 2
	};


	m_vertexArray = new VertexArray();
	m_vertexBuffer = new VertexBuffer(&m_Vertices[0], m_Vertices.size() * sizeof(float));
	m_Layout = new VertexBufferLayout();
	m_Layout->Push<float>(3);
	m_Layout->Push<float>(2);
	m_vertexArray->AddBuffer(*m_vertexBuffer, *m_Layout);
	m_IndexBuffer = new IndexBuffer(&m_Indices[0], m_Indices.size());

	m_Shader = new Shader("res/shaders/planeVertex.shader", "res/shaders/planeFrag.shader");
	m_Texture = new Texture("res/textures/normal_mapping_normal_map.png");
}

void Plane::Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightPos, glm::vec3 lightColor)
{
	m_Shader->Bind();
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, m_Position);
	model = glm::scale(model, m_Scale);

	m_Shader->setUniformMat4f("model", model);
	m_Shader->setUniformMat4f("view", view);
	m_Shader->setUniformMat4f("projection", projection);
	m_Shader->setUniform3f("Color", m_Color);
	m_Shader->setUniform3f("lightColor", lightColor);
	m_Shader->setUniform3f("lightPos", lightPos);

	m_Texture->Bind();
	m_vertexArray->Bind();
	m_IndexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}
