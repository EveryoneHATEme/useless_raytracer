#pragma once 

#include <optional>

#include "RayHit.h"

class RenderableObject
{
public:
	virtual ~RenderableObject() = default;

	virtual std::optional<RayHit> FindRayHit(const RayClass& ray, float minParameter, float maxParameter) const = 0;
};
