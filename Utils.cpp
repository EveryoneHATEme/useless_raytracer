#include "Utils.h"

Color Utils::vec3ToColor(const glm::vec3& source)
{
	glm::vec3 normalized = glm::clamp(glm::sqrt(source), 0.f, 1.f) * 255.f;

	return { (unsigned char)normalized.r, (unsigned char)normalized.g, (unsigned char)normalized.b, (unsigned char)255 };
}

glm::vec3 Utils::randomUnitOnHemisphere(const glm::vec3& normal)
{
	glm::vec3 newVector = glm::sphericalRand(1.f);
	return glm::dot(newVector, normal) > 0.f ? newVector : -newVector;
}