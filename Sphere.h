#ifndef SPHERE_H
#define SPHERE_H

#include <tuple>
#include "Vec3.h"

struct Sphere {
	Vec3 center;
	int radius;
	std::tuple<int, int, int> color; 

	Sphere(Vec3 center_, int radius_, std::tuple<int, int, int> color_) {
		this->center = center_;
		this->radius = radius_;
		this->color = color_;
	}
};
#endif // !SPHERE_H
