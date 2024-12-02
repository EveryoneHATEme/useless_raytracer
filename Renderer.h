#pragma once

#include "raylib.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>

#include "Viewport.h"
#include "RayClass.h"
#include "Utils.h"
#include "Scene.h"

class Renderer
{
private:
	unsigned int imageWidth;
	unsigned int imageHeight;

	unsigned int maxDepth = 50;
	unsigned int samplesPerPixel = 100;

	float sampleScale;

	Viewport* viewport;

	glm::vec3 GetPixel(unsigned int x, unsigned int y, const Scene& scene) const;

public:
	Renderer(unsigned int imWidth, unsigned int imHeight)
		: imageWidth(imWidth), imageHeight(imHeight)
	{
		viewport = new Viewport((float)imageWidth, (float)imageHeight);
		sampleScale = 1.0f / samplesPerPixel;
		std::cout << "sample scale: " << sampleScale << '\n';
	}

	void Render(Image& buffer, const Scene& scene) const;
	glm::vec3 Skybox(const RayClass& ray) const;
};