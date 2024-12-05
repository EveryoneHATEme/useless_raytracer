#pragma once

#include "raylib.h"
#include <glm/glm.hpp>

namespace Utils
{
	unsigned int wang_hash(unsigned int seed);

	Color vec3ToColor(const glm::vec3& source); 

	float RandomFloat();
	glm::vec3 RandomOnUnitSphere();
};