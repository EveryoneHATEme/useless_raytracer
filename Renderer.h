#pragma once

#include <memory>

#include <raylib.h>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include "Camera.h"
#include "HitPayload.h"
#include "RayClass.h"
#include "RenderableObject.h"
#include "Scene.h"

class Renderer
{
private:
	const Scene& scene;
	const CameraClass& camera;
	unsigned int maxDepth;

	std::vector<glm::vec3> rayDirectionsCache;

	glm::vec3 RenderPixel(unsigned int x, unsigned int y) const;
	HitPayload TraceRay(const RayClass& ray) const;
	HitPayload GetClosestHitPayload(const RayClass& ray, float hitDistance, std::shared_ptr<RenderableObject> hitObject) const;
	HitPayload GetMissPayload(const RayClass& ray) const;

public:
	Renderer(const Scene& scene, const CameraClass& camera, unsigned int maxDepth);

	void RenderScene(Image& buffer) const;
	void Update();
};