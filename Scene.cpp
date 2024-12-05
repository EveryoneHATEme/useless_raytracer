#include "Scene.h"

Scene::Scene(const std::vector<std::shared_ptr<RenderableObject>>& objects)
	:objects(objects)
{}

void Scene::AddObject(std::shared_ptr<RenderableObject> object)
{
	objects.push_back(object);
}

const std::vector<std::shared_ptr<RenderableObject>>& Scene::GetObjects() const
{
	return objects;
}
