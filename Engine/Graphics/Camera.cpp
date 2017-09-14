#include "Camera.h"



glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{

	float velocity = m_movementSpeed * deltaTime;

	// Moves the camera in the direction 

	if (direction == FORWARD)
		m_position += m_front * velocity;
	if (direction == BACKWARD)
		m_position -= m_front * velocity;
	if (direction == LEFT)
		m_position -= m_right * velocity;
	if (direction == RIGHT)
		m_position += m_right * velocity;


}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{

	xOffset *= m_mouseSensitivity;
	yOffset *= m_mouseSensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped.
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// Update m_front, m_right and m_up vectors using the Euler angles
	updateCameraVectors();

}

void Camera::processMouseScroll(GLfloat yOffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yOffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
		
}

// Calculates the front vector from the Camera's updated Euler Angles
void Camera::updateCameraVectors()
{
	// Calculate the new m_front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	
	// Also re-calculate the m_right and m_up vectors
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));

}


glm::vec3& Camera::getPosition() 
{
	return m_position;
}

glm::vec3 & Camera::getFront()
{
	return m_front;
}

glm::vec3 & Camera::getUp()
{
	return m_up;
}

glm::vec3 & Camera::getRight()
{
	return m_right;
}

glm::vec3 & Camera::getWorldUp()
{
	return m_worldUp;
}

GLfloat Camera::getYaw() const
{
	return m_yaw;
}

GLfloat Camera::getPitch() const
{
	return m_pitch;
}

GLfloat Camera::getMovementSpeed() const
{
	return m_movementSpeed;
}

GLfloat Camera::getMouseSensitivity() const
{
	return m_mouseSensitivity;
}

GLfloat Camera::getZoom() const
{
	return m_zoom;
}

GLfloat Camera::getFov() const
{
	return m_fov;
}

void Camera::setFov(GLfloat fov)
{
	m_fov = fov;
}
