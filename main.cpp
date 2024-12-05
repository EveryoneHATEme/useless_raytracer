#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "raylib.h"

#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

int main()
{
    SetTraceLogLevel(LOG_ERROR);

    unsigned int windowWidth = 640;
    unsigned int windowHeight = 480;

    InitWindow(windowWidth, windowHeight, "window");

    Scene scene;
    scene.AddObject(
        std::make_shared<Sphere>(Sphere(0.5f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.f, 0.f, 0.f)))
    );
    scene.AddObject(std::make_shared<Sphere>(Sphere(100.f, glm::vec3(0.0f, 100.5f, 1.0f), glm::vec3(0.f, 0.f, 1.f))));

    CameraClass camera(640, 480, glm::radians(45.f), 0.1f, 100.f);

    Renderer renderer(scene, camera, 50);

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