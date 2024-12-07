#pragma once

#include "raylib.h"
#include <glm/glm.hpp>

namespace Utils
{
	uint32_t wang_hash(uint32_t seed);
	uint32_t pcg_hash(uint32_t seed);

	Color vec3ToColor(const glm::vec3& source); 
	void CopyArrayToImage(const glm::vec3* source, Image& destination, float average);

	float RandomFloat();
	glm::vec3 RandomOnUnitSphere();
};