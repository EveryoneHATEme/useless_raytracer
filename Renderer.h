#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Scene.h"
#include "graphics/graphics.h"

class Renderer
{
private:
	Camera& camera;
	Scene& scene;

	unsigned int frameIndex{ 1u };
	
	std::unique_ptr<ShaderStorageBuffer> screenStorageBuffer;
	std::unique_ptr<Texture> displayTexture;
	std::unique_ptr<VertexArray> vertexArray;
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<Shader> displayShader;
	std::unique_ptr<Shader> copyShader;
	std::unique_ptr<Shader> raytracingShader;
	std::unique_ptr<UniformBuffer> dimensionsBuffer;
	std::unique_ptr<UniformBuffer> materialsBuffer;
	std::unique_ptr<UniformBuffer> spheresBuffer;

public:
	Renderer(Camera& camera, Scene& scene);
	~Renderer();

	void draw(GLFWwindow* window);
};