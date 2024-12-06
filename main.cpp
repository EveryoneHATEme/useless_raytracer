#pragma once

#define GLM_FORCE_INLINE

#include <memory>
#include <vector>
#include <iostream>

#include "raylib.h"

#include "Material.h"
#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

int main()
{
    SetTraceLogLevel(LOG_ERROR);

    unsigned int windowWidth = 1024;
    unsigned int windowHeight = 768;

    InitWindow(windowWidth, windowHeight, "window");

    MaterialStruct groundMaterial = { glm::vec3(0.f, 0.6f, 1.f), 0.f };
    MaterialStruct diffuseMaterial = { glm::vec3(1.f, 0.2f, 0.f), 0.f };
    MaterialStruct metalMaterial = { glm::vec3(0.4f, 0.4f, 0.4f), 0.5f };

    std::shared_ptr<Sphere> groundSphere = std::make_shared<Sphere>(100.f, glm::vec3(0.0f, 100.5f, 1.0f), groundMaterial);
    std::shared_ptr<Sphere> diffuseSphere = std::make_shared<Sphere>(0.5f, glm::vec3(1.0f, 0.0f, 0.0f), diffuseMaterial);
    std::shared_ptr<Sphere> metalSphere = std::make_shared<Sphere>(0.5f, glm::vec3(-1.0f, 0.0f, 0.0f), metalMaterial);

    Scene scene;
    scene.AddObject(groundSphere);
    scene.AddObject(diffuseSphere);
    scene.AddObject(metalSphere);

    CameraClass camera(windowWidth, windowHeight, glm::radians(45.f), 0.1f, 100.f);

    Renderer renderer(scene, camera, 5);

    Image currentImage = GenImageColor(windowWidth, windowHeight, WHITE);

    while (!WindowShouldClose())
    {
        float frameTime = GetFrameTime();
        camera.Update(frameTime);
        renderer.Update();

        renderer.RenderScene(currentImage);
        Texture2D currentTexture = LoadTextureFromImage(currentImage);

        BeginDrawing();

            ClearBackground(WHITE);
            DrawTexture(currentTexture, 0, 0, WHITE);
            DrawFPS(0, 0);

        EndDrawing();

        UnloadTexture(currentTexture);
        std::cout << "Rendered frame in " << frameTime << "s\n";
    }

    CloseWindow();

    return 0;
}