#pragma once

// DO NOT INCLUDE GLAD

#include <GLFW\glfw3.h>
#include "Camera.h"
#include <functional>

using namespace std;

class WindowManager
{

private: 
	GLuint m_width;
	GLuint m_height;
	const char* m_title = nullptr;

	GLfloat m_deltaTime = 0.0f;
	GLfloat m_lastFrame = 0.0f;

	GLboolean m_firstMouse;
	GLfloat m_lastX;
	GLfloat m_lastY;


public: 
	Camera camera;

	GLFWwindow* window;

	void(*fncPtr)(GLFWwindow, GLdouble, GLdouble);

	void createWindow(unsigned int width, unsigned int height, const char* title);

	void init();

	void update();

	void timeUpdate();

	void closeWindow();

	void processInput(GLFWwindow* window);
	
	void mouse_callback(GLFWwindow* window);

	void scroll_callback(GLFWwindow* window);

};
