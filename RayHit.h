#pragma once

#include <glm/glm.hpp>

#include "RayClass.h"

class RayHit
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	float parameter;
	bool frontFace;

	RayHit() = default;
	RayHit(float parameter, const glm::vec3& position, const glm::vec3& outwardNormal, const RayClass& ray);

	void setFaceNormal(const RayClass& ray, const glm::vec3& outwardNormal);
};