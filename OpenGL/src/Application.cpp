#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "texture.h"
#include "renderer.h"
#include "Camera.h"

#include <ASSIMP/Importer.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glewInit();

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Shader cubeShader("res/shaders/vertex.shader", "res/shaders/frag.shader");
	Shader lightShader("res/shaders/lightVertex.shader", "res/shaders/lightFrag.shader");

	std::vector<float> verts = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	};
	std::vector<unsigned int> indices = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	VertexArray va;
	VertexBuffer vb(&verts[0], verts.size() * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(&indices[0], indices.size());

	Renderer renderer;

	glm::mat4 view = camera.GetViewMatrix();

	glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Cube
	cubeShader.Bind();

	glm::mat4 cube = glm::mat4(1.0f);
	cube = glm::rotate(cube, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	cube = glm::scale(cube, glm::vec3(0.5f, 0.5f, 0.5f));
	cube = glm::translate(cube, glm::vec3(-1, 0, 0));

	cubeShader.setUniformMat4f("model", cube);
	cubeShader.setUniformMat4f("view", view);
	cubeShader.setUniformMat4f("projection", proj);

	cubeShader.setUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
	cubeShader.setUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
	cubeShader.setUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
	cubeShader.setUniform1f("material.shininess", 32.0f);


	//Light
	lightShader.Bind();

	glm::mat4 light = glm::mat4(1.0f);
	light = glm::rotate(light, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	light = glm::scale(light, glm::vec3(0.5f, 0.5f, 0.5f));
	light = glm::translate(light, glm::vec3(1, 0, 0));

	lightShader.setUniformMat4f("model", light);
	lightShader.setUniformMat4f("view", view);
	lightShader.setUniformMat4f("projection", proj);


	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);
		//Draw
		renderer.Clear();
		renderer.Draw(va, ib, cubeShader);
		renderer.Draw(va, ib, lightShader);
		//Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}