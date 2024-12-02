#pragma once

#include <optional>

#include <glm/glm.hpp>

#include "RenderableObject.h"
#include "RayClass.h"
#include "RayHit.h"

class Sphere : public RenderableObject
{
private:
	float radius;
	glm::vec3 position;
public:
	Sphere(float radius, const glm::vec3 position);
	float GetRadius() const;
	const glm::vec3& GetPosition() const;
	std::optional<RayHit> FindRayHit(const RayClass& ray, float minParameter, float maxParameter) const override;
};
