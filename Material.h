#pragma once

#include <glm/glm.hpp>

struct MaterialStruct
{
	glm::vec3 albedo{1.f};
	float diffuseRate = 1.f;
	float reflectanceRate = 0.f;

	glm::vec3 emissionColor{0.f};
	float emissionPower = 0.f;
};