#pragma once

#include <memory>
#include <vector>

#include "raylib.h"

#include "RenderableObject.h"
#include "Utils.h"
#include "HitPayload.h"

class Scene
{
private:
	std::vector<std::shared_ptr<RenderableObject>> objects;

public:
	Scene() = default;
	Scene(const std::vector<std::shared_ptr<RenderableObject>>& objects);

	void AddObject(std::shared_ptr<RenderableObject> object);

	const std::vector<std::shared_ptr<RenderableObject>>& GetObjects() const;
};