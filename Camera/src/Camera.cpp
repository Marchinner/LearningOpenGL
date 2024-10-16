#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
	front{ glm::vec3(0.0f, 0.0f, -1.0f) },
	movementSpeed{ SPEED },
	mouseSensitivity{ SENSITIVITY },
	zoom{ ZOOM },
	position{ position },
	worldUp{ up },
	yaw{ yaw },
	pitch{ pitch }
{
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	front{ glm::vec3(0.0f, 0.0f, -1.0f) },
	movementSpeed{ SPEED },
	mouseSensitivity{ SENSITIVITY },
	zoom{ ZOOM },
	position{ glm::vec3(posX, posY, posZ) },
	worldUp{ glm::vec3(upX, upY, upZ) },
	yaw{ yaw },
	pitch{ pitch }
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
	zoom -= (float)yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}
