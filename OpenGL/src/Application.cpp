#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "Mesh.h"
#include "Camera.h"

#include "Light.h"
#include "DiffuseCube.h"
#include "Plane.h"


#define WIN_HEIGHT 1200
#define WIN_WIDTH 1600

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	//------------------------------------------GLFW AND GLEW--------------------------------------------
	LOG("INITIALISING GLFW");
	if (!glfwInit())
	{
		LOG("FAILED TO INITALISE GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		LOG("FAILED TO CREATE GLFW WINDOW");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	LOG("INITIALISING GLEW");
	if (glewInit() != GLEW_OK)
	{
		LOG("FAILED TO INITALISE GLEW");
	}

	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//---------------------------------------------CAMERA-------------------------------------------------

	Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

	//---------------------------------------------SCEANE-------------------------------------------------

	glm::vec3 lightPos(0.0f, 1.0f, 0.0f);
	glm::vec3 lightColor(0.2f, 1.0f, 1.0f);

	Light light(lightPos, glm::vec3(1.0f), lightColor);
	Plane plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//------------------------------------------RENDER LOOP-----------------------------------------------

	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);
		//Render Commands
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Call Events
		glfwPollEvents();
		//Draw
		plane.Draw(camera.GetViewMatrix(), projection, lightPos, lightColor);
		//SwapBuffers
		glfwSwapBuffers(window);
	}

	//---------------------------------------------CLEANUP------------------------------------------------

	LOG("DESTROYING WINDOW");
	glfwDestroyWindow(window);

	LOG("TERMINATING GLFW");
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