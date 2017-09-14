#include <glad\glad.h>

#include <GLFW\glfw3.h>

#include "Graphics\WindowManager.h"
#include <iostream>
#include "Graphics\Loader.h"
#include "Graphics\Renderer.h"
#include "Graphics\ShaderManager.h"
#include "Graphics\TextureLoader.h"


// tutorial includes
#include "Graphics\TutorialLoader.h"

// GLM includes
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

// Initializing variables
GLfloat fov = 45.0f;


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

WindowManager windowManager;
GLFWwindow* window = nullptr;
Camera camera;

//Loader loader;

TutorialLoader tutorialLoader;
TextureLoader textureLoader;

Renderer renderer;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


int main()
{
	
	

	windowManager.init();

	windowManager.createWindow(SCR_WIDTH, SCR_HEIGHT, "Engine");
	
	window = windowManager.window;

	camera = windowManager.camera;

	// Try to find a better solution.
	glfwSetScrollCallback(window, scroll_callback);
	
	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Main.cpp::main() - " << "Failed to initialize GLAD" << std::endl;

	}
	
	std::cout << "Main.cpp::main() - " << "Successfully initialized GLFW and GLAD" << std::endl;


	GLuint program = 0;

	Managers::ShaderManager shaderManager;

	shaderManager.createProgram("testProgram",
		"C:\\dev\\GameEngine\\GameEngine\\Graphics\\Shaders\\vShader.vs",
		"C:\\dev\\GameEngine\\GameEngine\\Graphics\\Shaders\\fShader.fs");

	program = shaderManager.getProgram("testProgram");		

	/*
	shaderManager.createProgram("lightProgram",
		"C:\\dev\\GameEngine\\GameEngine\\Graphics\\Shaders\\lightShader.vs",
		"C:\\dev\\GameEngine\\GameEngine\\Graphics\\Shaders\\lightShader.fs");
	
	GLuint lightProgram = shaderManager.getProgram("lightProgram");
	*/

	glEnable(GL_DEPTH_TEST);

	

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	
	
	/*
	GLfloat vertices[] = {
		// positions			// textures coords
		 0.5f,  0.5f, 0.0f,		 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		 0.0f, 0.0f,	
		-0.5f,  0.5f, 0.0f,		 0.0f, 1.0f

	};
	
	*/

	// Ensure that the correct stride argument is given
	RawModel myModel = tutorialLoader.loadToVao(vertices, sizeof(vertices) / sizeof(GLfloat), 5);

	textureLoader.loadTexture("/Resources/Textures/wall.jpg");

	//RawModel lightSource = tutorialLoader.loadToVao(vertices, sizeof(vertices) / sizeof(GLfloat));


	GLuint vShader = shaderManager.getShader("testProgram", GL_FRAGMENT_SHADER);

	std::cout << "vShaderID for transformation: " << vShader << std::endl;

	
	
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


	double lastTime = glfwGetTime();
	int nbFrames = 0;

	
	int timeLoc = glGetUniformLocation(program, "time");

	while (!glfwWindowShouldClose(window))
	{
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
												// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// per-frame time logic
		windowManager.timeUpdate();


		// input
		// -----
		windowManager.processInput(window);
		windowManager.mouse_callback(window);
		

		// render
		// ------
		renderer.prepare();
	
		// create transformations
		
		shaderManager.startProgram(program);
		
		glUniform1f(timeLoc, currentTime);

		// Model matrix
		glm::mat4 model;
		//UNCOMMENT AFTER TEXTURE TESTING ON SIMPLE TRIANGLE
		//model = glm::rotate(model, (float)currentTime * glm::radians(-50.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 0.0f));

		shaderManager.setMat4("testProgram", "model", model);

		// View matrix
		glm::mat4 view;
		view = windowManager.camera.getViewMatrix();

		shaderManager.setMat4("testProgram", "view", view);

		// Projection matrix
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getFov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shaderManager.setMat4("testProgram", "projection", projection);
		

		renderer.render(myModel);


		shaderManager.stopProgram();

		

		
		// update window
		windowManager.update();

	}

	// Clean-up


	shaderManager.cleanUp();
	//loader.cleanUp();
	tutorialLoader.cleanUp();
	windowManager.closeWindow();

	

	return 0;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// Fires when GLFW notices a scroll event
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
	if (fov >= 1.0f && fov <= 45.0f)
		fov -=  yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;

	camera.setFov(fov);

	
}