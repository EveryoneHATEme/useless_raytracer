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
	CameraClass& camera;
	unsigned int maxDepth;

	bool antialiasing = true;

	unsigned int frameIndex{ 1u };

	glm::vec3* imageCache;
	std::vector<glm::vec3> rayDirectionsCache;

	glm::vec3 RenderPixel(unsigned int x, unsigned int y);
	HitPayload TraceRay(const RayClass& ray) const;
	HitPayload GetClosestHitPayload(const RayClass& ray, float hitDistance, std::shared_ptr<RenderableObject> hitObject) const;
	HitPayload GetMissPayload(const RayClass& ray) const;

public:
	Renderer(const Scene& scene, CameraClass& camera, unsigned int maxDepth);

	void RenderScene(Image& buffer);
	void Update();
};