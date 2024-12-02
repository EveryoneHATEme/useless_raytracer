#pragma once

#include "raylib.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

class Utils
{
public:
	static Color vec3ToColor(const glm::vec3& source);
	static glm::vec3 randomUnitOnHemisphere(const glm::vec3& normal);
};