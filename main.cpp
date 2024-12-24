#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include <iostream>

#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"


int main()
{
    unsigned int windowWidth = 1920;
    unsigned int windowHeight = 1080;

    float lastFrameTime;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize glew\n";
        return -1;
    }

    {
        Scene scene;
        scene.addMaterial({ glm::vec3(0.6f, 0.6f, 0.6f), 0.5f, glm::vec3(0.7f, 0.05f, 0.7f), 2.f }); // ground
        scene.addMaterial({ glm::vec3(1.0f, 0.2f, 0.2f), 0.3f, glm::vec3(0.f), 0.f }); // diffuse 
        scene.addMaterial({ glm::vec3(0.2f, 0.2f, 1.0f), 1.0f, glm::vec3(0.f), 0.f }); // metal 
        scene.addMaterial({ glm::vec3(1.f, 1.f, 1.f), 0.f, glm::vec3(0.1f, 0.1f, 1.f), 5.f }); // white light
        scene.addMaterial({ glm::vec3(1.f, 0.6f, 0.f), 0.f, glm::vec3(1.f, 0.6f, 0.01f), 10.f }); // yellow light

        scene.addSphere({ glm::vec3(0.0f, 100.5f, 1.0f), 100.f, 0, 0.0, 0.0, 0.0 }); // ground
        scene.addSphere({ glm::vec3(2.0f, 0.0f, 0.0f), 0.5f, 1, 0.0, 0.0, 0.0 }); // diffuse
        scene.addSphere({ glm::vec3(-2.0f, 0.0f, 0.0f), 0.5f, 2, 0.0, 0.0, 0.0 }); // metal
        scene.addSphere({ glm::vec3(0.0f, -2.0f, 3.0f), 0.5f, 3, 0.0, 0.0, 0.0 }); // white light
        scene.addSphere({ glm::vec3(0.0f, 0.0f, -3.0f), 0.5f, 4, 0.0, 0.0, 0.0 }); // yellow light

        Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(45.f), 0.1f, 100.f);

        Renderer renderer(camera, scene);

        lastFrameTime = (float)glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            float currentFrameTime = (float)glfwGetTime();
            float deltaTime = currentFrameTime - lastFrameTime;
            lastFrameTime = currentFrameTime;

            camera.update(window, deltaTime);
            renderer.draw(window);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    
    glfwTerminate();

    return 0;
}
