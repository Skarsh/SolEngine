
#include "WindowManager.h"
#include <iostream>


using namespace std;

void WindowManager::createWindow(unsigned int width, unsigned int height, const char* title)
{

	window = glfwCreateWindow(width, height, title, NULL, NULL);	// The 2 NULL Params could change.

	m_width = width;
	m_height = height;
	m_title = title;

	m_firstMouse = true;
	m_lastX = width / 2;
	m_lastY = height / 2;

	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));



	if (window == NULL)
	{
		std::cout << "WindowManager.cpp::createWindow() - " << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	
	glViewport(0, 0, width, height);
	glfwMakeContextCurrent(window);
	
	void (WindowManager::*fncPtr)(GLFWwindow, GLdouble, GLdouble);

	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

void WindowManager::init()
{
	// Init GLFW

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

}



void WindowManager::update()
{

	// Render here.??

	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void WindowManager::timeUpdate()
{
	// Calculates the time it takes for each frame
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

void WindowManager::closeWindow()
{

	glfwTerminate();

}


void WindowManager::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//std::cout << "WindowManager.cpp::processInput() - pressed W" << std::endl;
		camera.processKeyboard(FORWARD, m_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(LEFT, m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, m_deltaTime);

}

void WindowManager::mouse_callback(GLFWwindow* window)
{

	GLdouble xPos, yPos;

	glfwGetCursorPos(window, &xPos, &yPos);

//	std::cout << "xPos: " << xPos << " yPos: " << yPos << std::endl;

	// To get the mouse in the middle of the screen the first time the window is loaded.
	if (m_firstMouse)
	{
		m_lastX = xPos;
		m_lastY = yPos;
		m_firstMouse = false;
	}

	GLfloat xOffset = xPos - m_lastX;
	GLfloat yOffset = m_lastY - yPos;		// Reversed since y - coordinates go from bottom to top

	m_lastX = xPos;
	m_lastY = yPos;


	camera.processMouseMovement(xOffset, yOffset);

}

void WindowManager::scroll_callback(GLFWwindow * window)
{
	


}

