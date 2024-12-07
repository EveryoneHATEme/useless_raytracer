#include "Renderer.h"

#include <iostream>

glm::vec3 Renderer::RenderPixel(unsigned int x, unsigned int y)
{
	RayClass currentRay = RayClass(camera.GetPosition(), rayDirectionsCache[x + y * camera.getViewportWidth()]);

	glm::vec3 color(0.f);
	glm::vec3 throughput(1.f);

	for (unsigned int depth = 0u; depth < maxDepth; ++depth) {
		HitPayload hitPayload = TraceRay(currentRay);

		if (hitPayload.distance < 0.f) {
			//color += throughput * glm::vec3(0.01f, 0.01f, 0.015f);
			break;
		}

		MaterialStruct hitMaterial = hitPayload.object.get()->GetMaterial();

		throughput *= hitMaterial.albedo;
		color += hitMaterial.emissionColor * hitMaterial.emissionPower * throughput;

		float r = Utils::RandomFloat();
		glm::vec3 newDirection;

		if (r < hitMaterial.reflectanceRate) {
			throughput *= hitMaterial.reflectanceRate;
			newDirection = glm::reflect(currentRay.GetDirection(), hitPayload.normal);
		}
		else {
			newDirection = glm::normalize(hitPayload.normal + Utils::RandomOnUnitSphere());
		}

		currentRay = RayClass(hitPayload.position + hitPayload.normal * 0.0001f, newDirection);
	}

	return color;
}

HitPayload Renderer::TraceRay(const RayClass& ray) const
{
	float minHitDistance = std::numeric_limits<float>::infinity();
	std::shared_ptr<RenderableObject> closestObject = nullptr;
	float currentHitDistance = -1.f;
	
	for (const std::shared_ptr<RenderableObject>& object : scene.GetObjects()) {
		if (!object.get()->FindClosestIntersection(ray, currentHitDistance))
			continue;

		if (currentHitDistance > 0.f && currentHitDistance < minHitDistance) {
			minHitDistance = currentHitDistance;
			closestObject = object;
		}
	}

	if (closestObject == nullptr)
		return GetMissPayload(ray);

	return GetClosestHitPayload(ray, minHitDistance, closestObject);
}

HitPayload Renderer::GetClosestHitPayload(const RayClass& ray, float hitDistance, std::shared_ptr<RenderableObject> hitObject) const
{
	glm::vec3 hitPosition = ray.at(hitDistance);
	glm::vec3 hitNormal = glm::normalize(hitPosition - hitObject.get()->GetPosition());

	return { hitDistance, hitPosition, hitNormal, hitObject };
}

HitPayload Renderer::GetMissPayload(const RayClass& ray) const
{
	return { -1.f, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, nullptr };
}

Renderer::Renderer(const Scene& scene, CameraClass& camera, unsigned int maxDepth)
	:scene(scene), camera(camera), maxDepth(maxDepth)
{
	this->rayDirectionsCache.resize(camera.getViewportWidth() * camera.getViewportHeight());
	this->imageCache = new glm::vec3[camera.getViewportWidth() * camera.getViewportHeight()];
}

void Renderer::RenderScene(Image& buffer)
{
	if (this->camera.IsMoved()) {
		memset(this->imageCache, 0, this->camera.getViewportWidth() * this->camera.getViewportHeight() * sizeof(glm::vec3));
		this->frameIndex = 1u;
	}

	for (unsigned int y = 0u; y < camera.getViewportHeight(); ++y) 
		for (unsigned int x = 0u; x < camera.getViewportWidth(); ++x) 
			imageCache[x + y * camera.getViewportWidth()] += RenderPixel(x, y);

	Utils::CopyArrayToImage(this->imageCache, buffer, (float)frameIndex);

	++this->frameIndex;
}

void Renderer::Update()
{
	if (this->antialiasing || this->camera.IsMoved())
		camera.GetRayDirections(rayDirectionsCache);
}
