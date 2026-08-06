#include "Sphere.h"
#include "../core/Vec3.h"


Sphere::Sphere(Vec3 center_, float radius_, std::tuple<int, int, int> color_, int specular_, float reflective_) {
	this->center = center_;
	this->radius = radius_;
	this->color = color_;
	this->specular = specular_;
	this->reflective = reflective_;
}

Sphere::Sphere() {
	this->center = Vec3(0, 0, 0);
	this->radius = 0.0;
	this->color = std::tuple<int, int, int>(0, 0, 0);
	this->specular = 0;
	this->reflective = 0.0;
}