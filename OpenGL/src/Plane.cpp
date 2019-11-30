#include "Plane.h"
#include "GL/glew.h"


Plane::Plane(glm::vec3 position, std::string vertex, std::string frag, std::string diffuse, std::string normal, std::string height)
{
	// positions
	glm::vec3 pos1(-0.5f, 0.0f, -0.5f);
	glm::vec3 pos2(0.5f, 0.0f, -0.5f);
	glm::vec3 pos3(0.5f, 0.0f, 0.5f);
	glm::vec3 pos4(-0.5f, 0.0f, 0.5f);
	// tex coords
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(1.0f, 1.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(0.0f, 0.0f);
	// normal vector
	glm::vec3 nm(0.0f, 1.0f, 0.0f);

	// calculate tangent/bitangent vectors
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;

	// triangle one
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);

	// triangle two
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent2 = glm::normalize(bitangent2);


	float quadVertices[] = {
		//positions				normal			  texcoords		tangent								bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	};

	m_Indices = {
			0,2,1,
			0,3,2
	};



	vao = new VertexArray();
	vbo = new VertexBuffer(quadVertices, sizeof(quadVertices));
	ibo = new IndexBuffer(&m_Indices[0], m_Indices.size());
	vbl = new VertexBufferLayout();
	vbl->Push<float>(3);
	vbl->Push<float>(3);
	vbl->Push<float>(2);
	vbl->Push<float>(3);
	vbl->Push<float>(3);
	vao->AddBuffer(*vbo, *vbl);
	shader = new Shader(vertex, frag);
	shader->Bind();
	glm::mat4 model = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f), position), glm::vec3(5.0f)), glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setUniformMat4f("model", model); // Upload Model Matrix
	shader->setUniform1i("diffuseMap", 0);
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
	shader->setUniformMat4f("view", view); //Upload View Maxtrix
	shader->setUniformMat4f("projection", projection); //Upload Projection Matrix
	shader->setUniform3f("viewPos", cameraPos);
	shader->setUniform3f("lightPos", lightPos);
	m_diffuse->Bind(0);
	m_normal->Bind(1);
	m_displacement->Bind(2);
	glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
}
