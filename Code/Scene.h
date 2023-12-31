#pragma once
#include "dependencies.h"

struct Scene {

public:

	std::vector<Object*> objects;
	std::vector<Object*> area_lights;

	void addObject(Object* obj);
	void addAreaLight(Object* light);
	void addBox(Box* box);

	void rayTarget(Ray& ray) const;
	void traceRay(std::shared_ptr<Ray>& root) const;
	dvec3 localLighting(Ray& ray) const;
};