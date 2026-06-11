//This will include the function/procedure definitons for all the functions/procedures used in the book
//

#include "Constants.h"
#include "Vec3.h"
#include <tuple>
#include "Sphere.h"
#include <limits>
#include <cmath>
#include "Vector"

//method that returns the corresponding co-ordinate on the view port for a
//given point on the canvas
//
Vec3 canvasToViewPort(int x, int y) {
	int d = PROJECTTION_PLANE_D;
	return Vec3(x*(VIEWPORT_WIDTH/CANVAS_WIDTH), y*(VIEWPORT_HEIGHT/CANVAS_HEIGHT), d);
}

std::tuple<float, float> IntersectRaySphere(Vec3& O, Vec3& D, Sphere sphere) {
	float r = sphere.radius;
	Vec3 CO = O - sphere.center;

	float a = Vec3::dot(D, D);
	float b = 2 * Vec3::dot(CO, D);
	float c = Vec3::dot(CO, CO) - (r * r);

	float discriminant = b * b - (4 * a * c);

	if (discriminant < 0.0) {
		float posInf = std::numeric_limits<float>::infinity();
		return std::tuple<float, float >(posInf, posInf); //return infinity, infinity
	}

	float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b - std::sqrt(discriminant)) / (2 * a);

	return { t1, t2 };

}

std::tuple<int, int, int> TraceRay(Vec3& O, Vec3& D, float t_min, float t_max, std::vector<Sphere>& Spheres) {
	float closest_t = std::numeric_limits<float>::infinity();
	Sphere* closest_sphere = nullptr;

	for (Sphere currentSphere : Spheres) {
		std::tuple<float, float> t_values = IntersectRaySphere(O, D, currentSphere);
		float t1 = std::get<0>(t_values);
		float t2 = std::get<1>(t_values);

		if (((t1 >= t_min) && (t1 < t_max)) && t1 < closest_t) {
			closest_t = t1;
			closest_sphere = &currentSphere;

		}

		if (((t2 >= t_min) && (t2 < t_max)) && t2 < closest_t) {
			closest_t = t2;
			closest_sphere = &currentSphere;

		}
	}

	if (closest_sphere == nullptr) {
		return BACKGROUND_COLOUR;
	}

	std::tuple<int, int, int> color = closest_sphere->color;

	delete closest_sphere;
	closest_sphere = nullptr;

	return color;
}