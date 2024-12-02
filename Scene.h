#pragma once

#include <vector>
#include <optional>

#include "raylib.h"

#include "Sphere.h"
#include "Utils.h"
#include "RayHit.h"

class Scene
{
private:
	std::vector<Sphere> objects;

public:
	Scene() = default;
	Scene(const std::vector<Sphere>& objects);

	void AddObject(Sphere&& object);

	std::optional<RayHit> RayCast(const RayClass& ray, float minParameter, float maxParameter) const;
};