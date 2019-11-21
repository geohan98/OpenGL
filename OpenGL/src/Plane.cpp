#include "Plane.h"
#include "GL/glew.h"


Plane::Plane(glm::vec3 position, std::string vertex, std::string frag, std::string diffuse, std::string normal, std::string height)
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
	glm::mat4 model = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f), position), glm::vec3(5.0f)), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setUniformMat4f("model", model);
	shader->setUniform1i("ourTexture", 0);
	shader->setUniform1i("normalMap", 1);
	shader->setUniform1i("heightMap", 2);
	m_diffuse = new Texture(diffuse);
	m_normal = new Texture(normal);
	m_displacement = new Texture(height);
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
	m_diffuse->Bind(0);
	m_normal->Bind(1);
	m_displacement->Bind(2);
	glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
}
