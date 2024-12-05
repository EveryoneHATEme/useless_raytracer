#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "RenderableObject.h"
#include "RayClass.h"
#include "HitPayload.h"

class Sphere : public RenderableObject
{
private:
	float radius;
	glm::vec3 position;
	glm::vec3 color;
public:
	Sphere(float radius, glm::vec3 position, glm::vec3 color);

	float GetRadius() const;
	const glm::vec3& GetPosition() const;
	glm::vec3 GetColor() const override;

	std::vector<float> FindIntersections(const RayClass& ray) const override;
	bool FindClosestIntersection(const RayClass& ray, float& intersection) const override;
	glm::vec3 GetNormal(const glm::vec3& position) const override;
};
