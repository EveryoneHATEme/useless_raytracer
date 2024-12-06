#pragma once 

#include <vector>

#include <glm/glm.hpp>

#include "Material.h"
#include "RayClass.h"

class RenderableObject
{
public:
	virtual std::vector<float> FindIntersections(const RayClass& ray) const = 0;
	virtual bool FindClosestIntersection(const RayClass& ray, float& intersection) const = 0;
	virtual const MaterialStruct& GetMaterial() const = 0;
	virtual glm::vec3 GetNormal(const glm::vec3& position) const = 0;
	virtual const glm::vec3& GetPosition() const = 0;
};
