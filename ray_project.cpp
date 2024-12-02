#include "raylib.h"
#include <vector>
#include <iostream>

#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"

int main()
{
    SetTraceLogLevel(LOG_ERROR);

    unsigned int windowWidth = 640;
    unsigned int windowHeight = 480;

    InitWindow(windowWidth, windowHeight, "window");

    Renderer renderer(windowWidth, windowHeight);
    
    Scene scene;
    scene.AddObject(
        Sphere(0.5f, glm::vec3(0.0f, 0.0f, -1.0f))
    );
    scene.AddObject(
        Sphere(100.f, glm::vec3(0.0f, -100.5f, -1.0f))
    );

    Image currentImage;
    Texture2D currentTexture;

    while (!WindowShouldClose())
    {
        renderer.Render(currentImage, scene);
        currentTexture = LoadTextureFromImage(currentImage);

        BeginDrawing();

            ClearBackground(WHITE);
            DrawTexture(currentTexture, 0, 0, WHITE);

        EndDrawing();

        UnloadTexture(currentTexture);
        UnloadImage(currentImage);
        std::cout << "Rendered frame\n";
    }

    CloseWindow();

    return 0;
}