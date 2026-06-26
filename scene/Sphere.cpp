#include "Sphere.h"
#include "../core/Vec3.h"


Sphere::Sphere(Vec3 center_, float radius_, std::tuple<int, int, int> color_) {
	this->center = center_;
	this->radius = radius_;
	this->color = color_;
}