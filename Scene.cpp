#include "Scene.h"

void Scene::addMaterial(const Material& material)
{
	if (this->materialPayload.materialsCount < MATERIALS_SIZE)
		this->materialPayload.materials[this->materialPayload.materialsCount++] = material;
}

void Scene::addSphere(const Sphere& sphere)
{
	if (this->spherePayload.spheresCount < SPHERES_SIZE)
		this->spherePayload.spheres[this->spherePayload.spheresCount++] = sphere;
}

const MaterialPayload& Scene::getMaterialPayload() const
{
	return this->materialPayload;
}

const SpherePayload& Scene::getSpherePayload() const
{
	return this->spherePayload;
}
