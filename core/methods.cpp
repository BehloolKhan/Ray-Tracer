//This will include the function/procedure definitons for all the functions/procedures used in the book
//
#include "Constants.h"
#include "Vec3.h"
#include <tuple>
#include "../scene/Sphere.h"
#include <limits>
#include <cmath>
#include <vector>
#include <iostream>
#include "../scene/Scene.h"
#include "methods.h"
#include "../testFile.h"

//method that returns the corresponding co-ordinate on the view port for a
//given point on the canvas
//
Vec3 canvasToViewPort(int x, int y) {
	float d = (float) PROJECTTION_PLANE_D;
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

std::tuple<int, int, int> TraceRay(Vec3& O, Vec3& D, float t_min, float t_max, Scene& scene) {
	float closest_t = std::numeric_limits<float>::infinity();
	Sphere* closest_sphere = nullptr;

	for (Sphere& currentSphere : scene.getSpheres()) {

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

	//Now lets compute the intensity at the point of intersection
	//

	Vec3 P = O + Vec3::multiplier(D, closest_t);
	Vec3 N = P - closest_sphere->center;
	Vec3 N_normal = Vec3::divides(N, N.length());

	float intensity = computeLighting(P, N_normal, scene, closest_sphere->specular);
	std::tuple<int, int, int> color = closest_sphere->color;
	multiplyColorVector(color, intensity);
	closest_sphere = nullptr;

	return color;
}

float computeLighting(Vec3& P, Vec3& N, Scene& scene, int specular_) {
	float i = 0.0;
	P.printAll();
	N.printAll();
	for (Light* light: scene.getLights()){
		if (light->getType() == "ambient") {
			i += light->getIntensity();
		}
		else {
			Vec3 L;
			if (light->getType() == "point") {
				L = light->getPosition() - P;
			}

			else if (light->getType() == "directional") {
				L = light->getDirection();
			}

			//diffuse Reflection
			//
			float n_dot_L = Vec3::dot(N, L);
			if (n_dot_L >= 0.0) {
				i += (light->getIntensity() * n_dot_L / (N.length() * L.length()));
			}

			//specular Reflection
			//
			if (specular_ != -1) {

				Vec3 R = Vec3::multiplier(N, 2 * n_dot_L) - L;
				Vec3 V_ = origin - P;

				float cos_a = Vec3::dot(R, V_);
				cos_a = cos_a / (R.length() * V_.length());
				float cos_a_raised = std::pow(cos_a, (float)specular_);

				i += (light->getIntensity() * cos_a_raised);
			}
		}
	}

	//now we need to cap i

	if (i > 1.0) {
		return 1.0;
	}

	else if (i < 0.0) {
		return 0.0;
	}

	return i;
}

void multiplyColorVector(std::tuple<int, int, int>& color, float factor) {
	std::get<0>(color) = (int)(std::get<0>(color) * factor);
	std::get<1>(color) = (int)(std::get<1>(color) * factor);
	std::get<2>(color) = (int)(std::get<2>(color) * factor);
}