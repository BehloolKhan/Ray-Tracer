#ifndef SPHERE_H
#define SPHERE_H

#include <tuple>
#include "../core/Vec3.h"

struct Sphere {
	Vec3 center;
	float radius;
	std::tuple<int, int, int> color; 
	Sphere(Vec3 center_, float radius_, std::tuple<int, int, int> color_);
};
#endif
