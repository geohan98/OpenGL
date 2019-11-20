#include "Plane.h"
#include "GL/glew.h"


Plane::Plane(glm::vec3 position, std::string vertex, std::string frag, std::string tex)
{
	m_Vertices = {
			-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, 0.0f, -0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, 0.0f, 0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.0f, 0.5f,	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	};

	m_Indices = {
			0,1,2,
			0,2,3
	};

	vao = new VertexArray();
	vbo = new VertexBuffer(&m_Vertices[0], m_Vertices.size() * sizeof(float));
	ibo = new IndexBuffer(&m_Indices[0], m_Indices.size());
	vbl = new VertexBufferLayout();
	vbl->Push<float>(3);
	vbl->Push<float>(3);
	vbl->Push<float>(2);
	vao->AddBuffer(*vbo, *vbl);
	shader = new Shader(vertex, frag);
	shader->Bind();
	glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), position), glm::vec3(5.0f));
	shader->setUniformMat4f("model", model);
	texture = new Texture(tex);
}

void Plane::Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 lightPos)
{
	ibo->Bind();
	vbo->Bind();
	vao->Bind();
	shader->Bind();
	shader->setUniformMat4f("view", view);
	shader->setUniformMat4f("projection", projection);
	shader->setUniform3f("viewPos", cameraPos);
	shader->setUniform3f("lightPos", lightPos);
	texture->Bind();
	glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
}
