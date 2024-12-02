#pragma once

#include <glm/glm.hpp>

class RayClass
{
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	RayClass(const glm::vec3& origin, const glm::vec3& direction)
		:origin(origin), direction(direction)
	{}

	const glm::vec3& GetOrigin() const;
	const glm::vec3& GetDirection() const;
	glm::vec3 at(float t) const;
};