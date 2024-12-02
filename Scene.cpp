#include "Scene.h"

Scene::Scene(const std::vector<Sphere>& objects)
	:objects(objects)
{}

void Scene::AddObject(Sphere&& object)
{
	objects.emplace_back(std::move(object));
}

std::optional<RayHit> Scene::RayCast(const RayClass& ray, float minParameter, float maxParameter) const
{
	std::optional<RayHit> currentHit;
	RayHit closestHit;
	float closestParameter = maxParameter;
	bool hitAnything = false;

	for (const Sphere& object : objects) {
		currentHit = object.FindRayHit(ray, minParameter, closestParameter);
		if (not currentHit)
			continue;

		closestHit = currentHit.value();
		closestParameter = closestHit.parameter;
		hitAnything = true;
	}

	if (not hitAnything)
		return std::nullopt;

	return closestHit;
}

