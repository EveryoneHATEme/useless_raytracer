#include "RayHit.h"

RayHit::RayHit(float parameter, const glm::vec3& position, const glm::vec3& outwardNormal, const RayClass& ray)
	:parameter(parameter), position(position)
{
	setFaceNormal(ray, outwardNormal);
}

void RayHit::setFaceNormal(const RayClass& ray, const glm::vec3& outwardNormal)
{
	frontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
	normal = frontFace ? outwardNormal : -outwardNormal;
}
