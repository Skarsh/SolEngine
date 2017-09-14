#pragma once

// DO NOT INCLUDE GLAD

#include "GLFW\glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include <vector>

using namespace glm;



enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values. 
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{

	// VARIABLES

private:

	// Camera attributes
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	// Euler Angles
	GLfloat m_yaw;
	GLfloat m_pitch;

	// Camera options
	GLfloat m_movementSpeed;
	GLfloat m_mouseSensitivity;
	GLfloat m_zoom;
	GLfloat m_fov;					// Hardcoded FOV

public:



	// METHODS

private:

	void updateCameraVectors();

public:

	
	// Constructor with vectors
	Camera(glm::vec3 position = vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = vec3(0.0f, 1.0f, 0.0f),
			GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: m_position{ position }, m_worldUp{up}, m_yaw{yaw}, m_pitch{pitch}, 
		m_front{vec3(0.0f, 0.0f, -1.0f)}, m_movementSpeed{SPEED}, m_mouseSensitivity{SENSITIVITY}, m_zoom{ZOOM}
	{
		m_fov = 45.0f;				// HARDCODED FOV
		updateCameraVectors();
	}

	// Constructor with floats
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
		: m_position{ vec3(posX, posY, posZ) }, m_worldUp{ vec3(upX, upY, upZ) }, m_yaw{ yaw }, m_pitch{ pitch },
		m_front{ vec3(0.0f, 0.0f, -1.0f) }, m_movementSpeed{ SPEED }, m_mouseSensitivity{ SENSITIVITY }, m_zoom{ ZOOM }
	{
		m_fov = 45.0f;				// HARDCODED FOV
		updateCameraVectors();
	}

	


	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 getViewMatrix();
	

	void processKeyboard(Camera_Movement direction, GLfloat deltaTime);

	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

	void processMouseScroll(GLfloat yOffset);
	

	
	// Getter functions

	glm::vec3& getPosition();
	glm::vec3& getFront();
	glm::vec3& getUp();
	glm::vec3& getRight();
	glm::vec3& getWorldUp();

	GLfloat getYaw() const;
	GLfloat getPitch() const;
	GLfloat getMovementSpeed() const;
	GLfloat getMouseSensitivity() const;
	GLfloat getZoom() const;
	GLfloat getFov() const;

	// Setter functions

	void setFov(GLfloat fov);

};