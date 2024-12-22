#include "Camera.h"

#include <iostream>

Camera::Camera(unsigned int viewportWidth, unsigned int viewportHeight, glm::vec3 position, glm::vec3 forwardDirection, float verticalFOV, float nearClip, float farClip)
	: viewportWidth(viewportWidth), viewportHeight(viewportHeight), position(position), forwardDirection(forwardDirection), verticalFOV(verticalFOV), nearClip(nearClip), farClip(farClip)
{
	this->viewMatrix = glm::lookAt(this->position, this->position + this->forwardDirection, glm::vec3(0.f, 1.f, 0.f));
	this->inverseViewMatrix = glm::inverse(this->viewMatrix);
	this->projectionMatrix = glm::perspectiveFov(this->verticalFOV, (float)this->viewportWidth, (float)this->viewportHeight, this->nearClip, this->farClip);
	this->inverseProjectionMatrix = glm::inverse(this->projectionMatrix);
}

void Camera::update(GLFWwindow* window, float timeDelta)
{
	double inputXposDouble, inputYposDouble;
	glfwGetCursorPos(window, &inputXposDouble, &inputYposDouble);
	float inputXpos = (float)inputXposDouble;
	float inputYpos = (float)inputYposDouble;

	float pitchDelta = (this->lastCursorY - inputYpos) * this->mouseSensitivity;
	float yawDelta = (inputXpos - this->lastCursorX) * this->mouseSensitivity;
	
	this->lastCursorX = inputXpos;
	this->lastCursorY = inputYpos;

	this->moved = pitchDelta != 0.0f || yawDelta != 0.0f;
	
	constexpr glm::vec3 upDirection(0.f, 1.f, 0.f);
	glm::vec3 rightDirection = glm::cross(this->forwardDirection, upDirection);
	float distance = this->movementSpeed * timeDelta;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W)) {
		this->position += this->forwardDirection * distance;
		this->moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		this->position -= this->forwardDirection * distance;
		this->moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		this->position -= rightDirection * distance;
		this->moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		this->position += rightDirection * distance;
		this->moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		this->position -= upDirection * distance;
		this->moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_C)) {
		this->position += upDirection * distance;
		this->moved = true;
	}

	glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection), glm::angleAxis(-yawDelta, upDirection)));
	this->forwardDirection = glm::rotate(q, this->forwardDirection);

	this->viewMatrix = glm::lookAt(this->position, this->position + this->forwardDirection, upDirection);
	this->inverseViewMatrix = glm::inverse(this->viewMatrix);
}
