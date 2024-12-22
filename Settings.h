#pragma once

#include <glm/glm.hpp>


constexpr size_t MATERIALS_SIZE = 8;
constexpr size_t SPHERES_SIZE = 8;

struct Material
{
    glm::vec3 albedo;
    float reflectanceRate;
    glm::vec3 emissionColor;
    float emissionPower;
};

struct Sphere
{
    glm::vec3 origin;
    float radius;
    unsigned int materialIndex;
    float padding0;
    float padding1;
    float padding2;
};
