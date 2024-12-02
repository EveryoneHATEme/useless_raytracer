#include "Renderer.h"


glm::vec3 Renderer::GetPixel(unsigned int x, unsigned int y, const Scene& scene) const
{
	RayClass ray = viewport->GetRay(x, y);
	std::optional<RayHit> rayHit;

	float coefficient = 1.f;
	unsigned int currentDepth = 0;

	for (; currentDepth < maxDepth; ++currentDepth)
	{
		rayHit = scene.RayCast(ray, 0.001f, std::numeric_limits<float>::infinity());
		if (not rayHit)
			break;

		coefficient *= 0.5;
		ray = RayClass(rayHit.value().position, rayHit.value().normal + glm::sphericalRand(1.f));
	}

	glm::vec3 finalColor = Skybox(ray) * coefficient;

	return finalColor;
}

void Renderer::Render(Image& buffer, const Scene& scene) const
{
	buffer = GenImageColor(imageWidth, imageHeight, WHITE);
	glm::vec3 pixelColorVector(0.f, 0.f, 0.f);
	Color pixelColor;

	for (unsigned int y = 0; y < imageHeight; ++y) {
		for (unsigned int x = 0; x < imageWidth; ++x) {
			pixelColorVector = glm::vec3(0.f, 0.f, 0.f);

			for (unsigned int sample = 0; sample < samplesPerPixel; ++sample)
				pixelColorVector += GetPixel(x, y, scene);

			pixelColor = Utils::vec3ToColor(pixelColorVector * sampleScale);
			ImageDrawPixel(&buffer, x, y, pixelColor);
		}
	}
}

glm::vec3 Renderer::Skybox(const RayClass& ray) const
{
	float parameter = 0.5f * (ray.GetDirection().y + 1.0f);
	glm::vec3 firstColor(1.0f, 1.0f, 1.0f);
	glm::vec3 secondColor(0.5f, 0.7f, 1.0f);

	glm::vec3 currentColor = (1.0f - parameter) * firstColor + parameter * secondColor;
	return currentColor;
}