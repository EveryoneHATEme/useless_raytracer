#pragma once

#include <array>

#include <glm/glm.hpp>

#include "Settings.h"


struct MaterialPayload
{
    Material materials[MATERIALS_SIZE];
    unsigned int materialsCount = 0;
    float padding0;
    float padding1;
    float padding2;
};

struct SpherePayload
{
    Sphere spheres[SPHERES_SIZE];
    unsigned int spheresCount = 0;
    float padding0;
    float padding1;
    float padding2;
};

class Scene
{
private:
    MaterialPayload materialPayload;
    SpherePayload spherePayload;

public:
    Scene() {};
    
    void addMaterial(const Material& material);
    void addSphere(const Sphere& sphere);

    const MaterialPayload& getMaterialPayload() const;
    const SpherePayload& getSpherePayload() const;
};