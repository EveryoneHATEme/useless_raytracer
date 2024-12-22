#include "Renderer.h"

Renderer::Renderer(Camera& camera, Scene& scene)
	:camera(camera), scene(scene)
{
    this->screenStorageBuffer = std::make_unique<ShaderStorageBuffer>(this->camera.getViewportWidth() * this->camera.getViewportHeight() * sizeof(float) * 4);
    this->screenStorageBuffer->setBindingPoint(0);

    this->displayTexture = std::make_unique<Texture>(this->camera.getViewportWidth(), this->camera.getViewportHeight());

    float quadVertices[8] = {
        -1.f, -1.f,
        1.f, -1.f,
        -1.f, 1.f,
        1.f, 1.f
    };
    this->vertexBuffer = std::make_unique<VertexBuffer>(sizeof(quadVertices), quadVertices);

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push<float>(2);

    this->vertexArray = std::make_unique<VertexArray>();
    this->vertexArray->addBuffer(*this->vertexBuffer.get(), vertexBufferLayout);

    this->displayShader = std::make_unique<Shader>("vertex_shader.vert", "fragment_shader.frag", nullptr);
    this->copyShader = std::make_unique<Shader>(nullptr, nullptr, "copy_shader.comp");
    this->raytracingShader = std::make_unique<Shader>(nullptr, nullptr, "raytracing_shader.comp");

    int dimensions[2]{ (int)this->camera.getViewportWidth(), (int)this->camera.getViewportHeight() };

    this->dimensionsBuffer = std::make_unique<UniformBuffer>(dimensions, 2 * sizeof(int), 0);
    this->materialsBuffer = std::make_unique<UniformBuffer>(&this->scene.getMaterialPayload(), sizeof(MaterialPayload), 1);
    this->spheresBuffer = std::make_unique<UniformBuffer>(&this->scene.getSpherePayload(), sizeof(SpherePayload), 2);

    this->dimensionsBuffer->setShaderBinding(this->raytracingShader->getID(), "ScreenDimensions");
    this->dimensionsBuffer->setShaderBinding(this->copyShader->getID(), "ScreenDimensions");
    
    this->materialsBuffer->setShaderBinding(this->raytracingShader->getID(), "MaterialBlock");

    this->spheresBuffer->setShaderBinding(this->raytracingShader->getID(), "SphereBlock");
}

Renderer::~Renderer()
{
}


void Renderer::draw(GLFWwindow* window)
{
    if (camera.isMoved())
        this->frameIndex = 1u;
    else
        this->frameIndex++;

    this->raytracingShader->use();
    this->raytracingShader->setInt("frameCount", this->frameIndex);
    this->raytracingShader->setMat4("inverseViewMatrix", this->camera.getInverseViewMatrix());
    this->raytracingShader->setMat4("inverseProjectionMatrix", this->camera.getInverseProjectionMatrix());
    this->raytracingShader->setVec3("cameraPosition", this->camera.getPosition());

    glDispatchCompute((this->camera.getViewportWidth() + 15) / 16, (this->camera.getViewportHeight() + 15) / 16, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    this->copyShader->use();

    glBindImageTexture(1, this->displayTexture->getID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute((this->camera.getViewportWidth() + 15) / 16, (this->camera.getViewportHeight() + 15) / 16, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glClear(GL_COLOR_BUFFER_BIT);
    this->displayShader->use();
    this->displayTexture->bind(0);
    this->displayShader->setInt("displayTex", 0);
    this->vertexArray->bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    this->vertexArray->unbind();
    displayTexture->unbind();
}