#ifndef SPHERE_H
#define SPHERE_H

#include <tuple>
#include "../core/Vec3.h"

struct Sphere {
	Vec3 center;
	float radius;
	std::tuple<int, int, int> color; 
	int specular;
	float reflective; //shows how reflective surface is, 0.0 - not, 1.0-very;
	Sphere(Vec3 center_, float radius_, std::tuple<int, int, int> color_, int specular_, float reflective_);
	Sphere(); //defualut constructor
};
#endif
