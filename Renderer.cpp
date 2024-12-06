#include "Renderer.h"

#include <iostream>

glm::vec3 Renderer::RenderPixel(unsigned int x, unsigned int y) const
{
	RayClass currentRay = RayClass(camera.GetPosition(), rayDirectionsCache[x + y * camera.getViewportWidth()]);

	glm::vec3 color(0.f);
	glm::vec3 throughput(1.f);
	float attenuation = 0.5f;

	for (unsigned int depth = 0u; depth < maxDepth; ++depth) {
		HitPayload hitPayload = TraceRay(currentRay);

		if (hitPayload.distance < 0.f) {
			color += throughput * glm::vec3(0.7f);
			break;
		}

		MaterialStruct hitMaterial = hitPayload.object.get()->GetMaterial();
		glm::vec3 diffuse = hitMaterial.diffuseColor * (1.f - hitMaterial.reflectanceRate);
		color += throughput * diffuse * attenuation;

		glm::vec3 reflectDirection = glm::reflect(currentRay.GetDirection(), hitPayload.normal);
		glm::vec3 diffuseDirection = glm::normalize(hitPayload.normal + Utils::RandomOnUnitSphere());

		float r = Utils::RandomFloat();
		glm::vec3 newDirection;

		if (r < hitMaterial.reflectanceRate) {
			throughput *= hitMaterial.reflectanceRate;
			newDirection = glm::reflect(currentRay.GetDirection(), hitPayload.normal);
		}
		else {
			throughput *= hitMaterial.diffuseColor * (1.f - hitMaterial.reflectanceRate);
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
	glm::vec3 origin = ray.GetOrigin() - hitObject.get()->GetPosition();
	glm::vec3 hitPosition = origin + ray.GetDirection() * hitDistance;
	glm::vec3 hitNormal = glm::normalize(hitPosition);
	hitPosition += hitObject.get()->GetPosition();

	return { hitDistance, hitPosition, hitNormal, hitObject };
}

HitPayload Renderer::GetMissPayload(const RayClass& ray) const
{
	return { -1.f, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, nullptr };
}

Renderer::Renderer(const Scene& scene, const CameraClass& camera, unsigned int maxDepth)
	:scene(scene), camera(camera), maxDepth(maxDepth)
{
	rayDirectionsCache.resize(camera.getViewportWidth() * camera.getViewportHeight());
}

void Renderer::RenderScene(Image& buffer) const
{
	glm::vec3 pixelColor;
	Color normalizedColor;

	for (unsigned int y = 0u; y < camera.getViewportHeight(); ++y) {
		for (unsigned int x = 0u; x < camera.getViewportWidth(); ++x) {
			pixelColor = RenderPixel(x, y);
			normalizedColor = Utils::vec3ToColor(pixelColor);
			ImageDrawPixel(&buffer, x, y, normalizedColor);
		}
	}
}

void Renderer::Update()
{
	camera.GetRayDirections(rayDirectionsCache);
}
