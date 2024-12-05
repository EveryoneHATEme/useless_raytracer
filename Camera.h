#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <raylib.h>

#include "RayClass.h"
#include "Utils.h"

class CameraClass
{
private:
	unsigned int viewportWidth;
	unsigned int viewportHeight;

	float verticalFOV;
	float nearClip;
	float farClip;

	glm::mat4 projection{ 1.0f };
	glm::mat4 view{ 1.0f };
	glm::mat4 inverseProjection{ 1.0f };
	glm::mat4 inverseView{ 1.0f };

	glm::vec3 position{ 0.0f, 0.0f, 2.0f };
	glm::vec3 forwardDirection{ 0.0f, 0.0f, 1.0f };

public:
	CameraClass(unsigned int viewportWidth, unsigned int viewportHeight, float verticalFOV, float nearClip, float farClip);

	void GetRayDirections(std::vector<glm::vec3>& rayDirections) const;
	void Update(float timeDelta);
	
	unsigned int getViewportWidth() const { return viewportWidth; }
	unsigned int getViewportHeight() const { return viewportHeight; }

	glm::vec3 GetPosition() const { return position; }
};

