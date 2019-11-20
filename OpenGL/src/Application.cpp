#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Camera.h"
#include "Plane.h"



#define WIN_HEIGHT 600
#define WIN_WIDTH 800

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0, -0.17365, -0.98481);
glm::vec3 cameraUp = glm::vec3(0, 0.98481, -0.17365);

float fov = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//---------------------------------------------SCEANE-------------------------------------------------
	glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);

	Plane planeAmbient(glm::vec3(0.0f, 0.0f, 0.0f), "res/shaders/ambient.vert", "res/shaders/ambient.frag", "res/textures/GitHub-Mark.png");
	Plane planeDiffuse(glm::vec3(5.0f, 0.0f, 0.0f), "res/shaders/diffuse.vert", "res/shaders/diffuse.frag", "res/textures/GitHub-Mark.png");
	Plane planeSpecular(glm::vec3(10.0f, 0.0f, 0.0f), "res/shaders/specular.vert", "res/shaders/specular.frag", "res/textures/GitHub-Mark.png");
	Plane planePhong(glm::vec3(15.0f, 0.0f, 0.0f), "res/shaders/phong.vert", "res/shaders/phong.frag", "res/textures/GitHub-Mark.png");
	Plane planeBlinnPhong(glm::vec3(20.0f, 0.0f, 0.0f), "res/shaders/blinnPhong.vert", "res/shaders/blinnPhong.frag", "res/textures/GitHub-Mark.png");
	Plane planeTexPhong(glm::vec3(25.0f, 0.0f, 0.0f), "res/shaders/texPhong.vert", "res/shaders/texPhong.frag", "res/textures/GitHub-Mark-Light.png");

	//----------------------------------------------CAMERA-----------------------------------------------

	//------------------------------------------RENDER LOOP-----------------------------------------------

	while (!glfwWindowShouldClose(window))
	{
		lightPos = cameraPos + glm::vec3(0.0f, 0.0f, -10.0f);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//Input
		processInput(window);
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//Render Commands
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Draw
		planeAmbient.Draw(view, projection, cameraPos, lightPos);
		planeDiffuse.Draw(view, projection, cameraPos, lightPos);
		planeSpecular.Draw(view, projection, cameraPos, lightPos);
		planePhong.Draw(view, projection, cameraPos, lightPos);
		planeTexPhong.Draw(view, projection, cameraPos, lightPos);
		planeBlinnPhong.Draw(view, projection, cameraPos, lightPos);
		//SwapBuffers
		glfwSwapBuffers(window);
		//Call Events
		glfwPollEvents();


	}

	//---------------------------------------------CLEANUP------------------------------------------------

	LOG("DESTROYING WINDOW");
	glfwDestroyWindow(window);

	LOG("TERMINATING GLFW");
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}