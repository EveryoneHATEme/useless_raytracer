#include "Viewport.h"

Viewport::Viewport(float imageWidth, float imageHeight)
	:imageWidth(imageWidth), imageHeight(imageHeight)
{
	aspectRatio = imageWidth / imageHeight;
	InitializeVariables();
}

glm::vec3 Viewport::GetPixelCoordinate(unsigned int x, unsigned int y) const
{
	return zeroPixelLocation + (float(x) * horizontalPixelDelta) + (float(y) * verticalPixelDelta);
}

RayClass Viewport::GetRay(unsigned int x, unsigned int y) const
{
	glm::vec2 offset = glm::diskRand(0.5f);
	glm::vec3 pixelSample = zeroPixelLocation + (x + offset.x) * horizontalPixelDelta + (y + offset.y) * verticalPixelDelta;
	glm::vec3 rayOrigin = cameraCenter;
	glm::vec3 rayDirection = pixelSample - rayOrigin;

	return RayClass(rayOrigin, rayDirection);
}

const glm::vec3& Viewport::GetCameraCenter() const
{
	return cameraCenter;
}

void Viewport::InitializeVariables() {
	viewportWidth = viewportHeight * aspectRatio;

	viewportHorizontal = glm::vec3(viewportWidth, 0.0, 0.0);
	viewportVertical = glm::vec3(0.0, -viewportHeight, 0.0);

	horizontalPixelDelta = viewportHorizontal / (float)imageWidth;
	verticalPixelDelta = viewportVertical / (float)imageHeight;

	viewportUpperLeft = cameraCenter - glm::vec3(0.0, 0.0, focalLength) - (viewportHorizontal + viewportVertical) / 2.0f;
	zeroPixelLocation = viewportUpperLeft + (horizontalPixelDelta + verticalPixelDelta) / 2.0f;
}