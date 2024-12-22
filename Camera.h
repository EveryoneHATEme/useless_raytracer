#pragma once

#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GLFW/glfw3.h>


class Camera
{
private:
	unsigned int viewportWidth;
	unsigned int viewportHeight;

	float verticalFOV;
	float nearClip;
	float farClip;

	bool moved{ true };

	glm::mat4 projectionMatrix{ 1.0f };
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 inverseProjectionMatrix{ 1.0f };
	glm::mat4 inverseViewMatrix{ 1.0f };

	glm::vec3 position{ 0.0f, 0.0f, 2.0f };
	glm::vec3 forwardDirection{ 0.0f, 0.0f, 1.0f };

	float movementSpeed = 2.5f;
	float mouseSensitivity = 0.005f;

	float lastCursorX = 0.0f;
	float lastCursorY = 0.0f;

public:
	Camera(unsigned int viewportWidth, unsigned int viewportHeight, glm::vec3 position, glm::vec3 forwardDirection, float verticalFOV, float nearClip, float farClip);

	void update(GLFWwindow* window, float timeDelta);
	
	unsigned int getViewportWidth() const { return this->viewportWidth; }
	unsigned int getViewportHeight() const { return this->viewportHeight; }
	float getMovementSpeed() const { return this->movementSpeed; }
	float getMouseSensitivity() const { return this->mouseSensitivity; }
	bool isMoved() const { return this->moved; };
	const glm::mat4& getInverseViewMatrix() const { return this->inverseViewMatrix; }
	const glm::mat4& getInverseProjectionMatrix() const { return this->inverseProjectionMatrix; }

	glm::vec3 getPosition() const { return this->position; }
};

