#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "RenderableObject.h"

typedef struct HitPayload
{
	float distance;
	glm::vec3 position;
	glm::vec3 normal;
	std::shared_ptr<RenderableObject> object;

} HitPayload;