#include "Sphere.h"

Sphere::Sphere(float radius, const glm::vec3 position)
	:radius(std::fmax(0.f, radius)), position(position)
{
}

float Sphere::GetRadius() const
{
	return radius;
}

const glm::vec3& Sphere::GetPosition() const
{
	return position;
}

std::optional<RayHit> Sphere::FindRayHit(const RayClass& ray, float minParameter, float maxParameter) const
{
	glm::vec3 oc = position - ray.GetOrigin();

	float a = glm::dot(ray.GetDirection(), ray.GetDirection());
	float h = glm::dot(ray.GetDirection(), oc);
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = h * h - a * c;

	if (discriminant < 0)
		return std::nullopt;

	float discriminantSqrt = std::sqrt(discriminant);

	float parameter = (h - discriminantSqrt) / a;
	if (parameter <= minParameter || parameter >= maxParameter) {
		parameter = (h + discriminantSqrt) / a;
		if (parameter <= minParameter || parameter >= maxParameter)
			return std::nullopt;
	}

	glm::vec3 hitPosition = ray.at(parameter);
	glm::vec3 outwardNormal = (hitPosition - position) / radius;

	RayHit rayHit(parameter, hitPosition, outwardNormal, ray);

	return rayHit;
}