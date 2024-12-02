#include "RayClass.h"

const glm::vec3& RayClass::GetOrigin() const
{
	return origin;
}

const glm::vec3& RayClass::GetDirection() const
{
	return direction;
}

glm::vec3 RayClass::at(float t) const
{
	return origin + t * direction;
}