#include "Sphere.h"
#include <iostream>

Sphere::Sphere(float radius, glm::vec3 position, glm::vec3 color)
	:radius(std::fmax(0.f, radius)), position(position), color(color)
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

glm::vec3 Sphere::GetColor() const
{
	return color;
}

std::vector<float> Sphere::FindIntersections(const RayClass& ray) const
{
	std::vector<float> result;
	result.reserve(2);
	glm::vec3 origin = ray.GetOrigin() - position;

	float a = glm::dot(ray.GetDirection(), ray.GetDirection());
	float b = 2.f * glm::dot(origin, ray.GetDirection());
	float c = glm::dot(origin, origin) - radius * radius;

	float discriminant = b * b - 4.f * a * c;
	if (discriminant == 0.f) {
		result.push_back(-b / (2.f * a));
	}
	else if (discriminant > 0.f) {
		float discriminantSqrt = glm::sqrt(discriminant);
		result.push_back((-b - discriminantSqrt) / (2.f * a));
		result.push_back((-b + discriminantSqrt) / (2.f * a));
	}

	return result;
}

bool Sphere::FindClosestIntersection(const RayClass& ray, float& intersection) const
{
	glm::vec3 origin = ray.GetOrigin() - position;

	float a = glm::dot(ray.GetDirection(), ray.GetDirection());
	float b = 2.f * glm::dot(origin, ray.GetDirection());
	float c = glm::dot(origin, origin) - radius * radius;

	float discriminant = b * b - 4.f * a * c;

	if (discriminant < 0.f)
		return false;

	intersection = (-b - glm::sqrt(discriminant)) / (2.f * a);
	return true;
}

glm::vec3 Sphere::GetNormal(const glm::vec3& position) const
{
	return glm::normalize(position - this->position);
}