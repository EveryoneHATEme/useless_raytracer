#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include "RayClass.h"


class Viewport
{
private:
	float imageWidth;
	float imageHeight;

	float aspectRatio;
	float focalLength = 1.f;
	float viewportWidth;
	float viewportHeight = 2.f;

	glm::vec3 cameraCenter = glm::vec3(0, 0, 0);
	glm::vec3 viewportHorizontal;
	glm::vec3 viewportVertical;

	glm::vec3 horizontalPixelDelta;
	glm::vec3 verticalPixelDelta;

	glm::vec3 viewportUpperLeft;
	glm::vec3 zeroPixelLocation;

	void InitializeVariables();
public:
	Viewport(float imageWidth, float imageHeight);

	const glm::vec3& GetCameraCenter() const;
	glm::vec3 GetPixelCoordinate(unsigned int x, unsigned int y) const;
	RayClass GetRay(unsigned int x, unsigned int y) const;
};