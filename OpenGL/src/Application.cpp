#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "texture.h"
#include "renderer.h"

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

	Shader shader("res/shaders/vertex.shader", "res/shaders/frag.shader");
	shader.setUniform1i("u_Texture", 0);

	Texture texture("res/textures/wall.jpg");

	float vertices[6 * 24] = {
				-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
				 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
				 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
				-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
				-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
				 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
				 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
				-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
				-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
				 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
				 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
				-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
				-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
				 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
				 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
				-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
				-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
				-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
				-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
				-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
				0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
				0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
				0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
				0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
	};

	unsigned int indices[3 * 12] = {
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
	VertexBuffer vb(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 36);



	Renderer renderer;

	shader.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setUniformMat4f("model", model);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	shader.setUniformMat4f("view", view);

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.3f, 0.1f, 100.0f);
	shader.setUniformMat4f("proj", proj);

	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);
		//Draw
		shader.Bind();
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f) / 500, glm::vec3(0.5f, 1.0f, 0.0f));
		shader.setUniformMat4f("model", model);
		shader.Unbind();
		

		renderer.Clear();
		texture.Bind();
		renderer.Draw(va, ib, shader);
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