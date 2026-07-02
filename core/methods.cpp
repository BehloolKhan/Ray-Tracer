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

std::tuple<Sphere*, float>closestIntersection(Vec3& O, Vec3& direction_, float t_min, float t_max, Scene& scene) {
	float closest_t = std::numeric_limits<float>::infinity();
	Sphere* closest_sphere = nullptr;

	for (Sphere& currentSphere : scene.getSpheres()) {

		std::tuple<float, float> t_values = IntersectRaySphere(O, direction_, currentSphere);
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

	return {closest_sphere, closest_t};
}

std::tuple<int, int, int> TraceRay(Vec3& O, Vec3& D, float t_min, float t_max, Scene& scene, int recursionDepth) {

	std::tuple<Sphere*, float> results = closestIntersection(O, D, t_min, t_max, scene);

	if (std::get<0>(results) == nullptr) {
		return BACKGROUND_COLOUR;
	}

	//Now lets compute the intensity at the point of intersection
	//
	Vec3 P = O + Vec3::multiplier(D, std::get<1>(results));
	Vec3 N = P - std::get<0>(results)->center;
	Vec3 N_normal = Vec3::divides(N, N.length());


	float intensity = computeLighting(O, P, N_normal, scene, std::get<0>(results)->specular);
	std::tuple<int, int, int> localColor = std::get<0>(results)->color;
	multiplyColorVector(localColor, intensity);

	float r = std::get<0>(results)->reflective;
	if((recursionDepth <= 0 ) || (r<=0.0)) {
		return localColor;
	}

	Vec3 R = reflectRay(-D, N_normal);
	std::tuple<int, int, int> reflectedColor = TraceRay(P, R, (float)0.001, std::numeric_limits<float>::infinity(), scene, recursionDepth-1);

	multiplyColorVector(localColor, (float)1.0-r);
	multiplyColorVector(reflectedColor, r);

	return addTwoColors(localColor, reflectedColor);
}

float computeLighting(Vec3& O, Vec3& P, Vec3& N, Scene& scene, int specular_) {
	float i = 0.0;
	P.printAll();
	N.printAll();

	for (Light* light: scene.getLights()){
		if (light->getType() == "ambient") {
			i += light->getIntensity();
		}
		else {
			float t_max = std::numeric_limits<float>::infinity(); //by default we will assume light is directional and then change t_max
			//if it is not

			Vec3 L;
			if (light->getType() == "point") {
				L = light->getPosition() - P;
				t_max = 1;
			}

			else if (light->getType() == "directional") {
				L = light->getDirection();
			}

			//checking to see if there is a shadow
			//
			std::tuple<Sphere*, float> results = closestIntersection(P, L, (float)0.001, t_max, scene);

			if (std::get<0>(results) == nullptr) { //no intersection between point P and source of light
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
					Vec3 V_ = O - P;

					float cos_a = Vec3::dot(R, V_);
					cos_a = cos_a / (R.length() * V_.length());
					float cos_a_raised = std::pow(cos_a, (float)specular_);

					i += (light->getIntensity() * cos_a_raised);
				}
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

Vec3 reflectRay(Vec3& R, Vec3& N) {
	float a = 2*Vec3::dot(R, N);
	Vec3 vector = Vec3::multiplier(N, a) - R;
	return vector;
}

std::tuple<int, int, int> addTwoColors(std::tuple<int, int, int>& color, std::tuple<int, int, int>& colorOne) {
	int value1 = std::get<0>(color) + std::get<0>(colorOne);
	int value2 = std::get<1>(color) + std::get<1>(colorOne);
	int value3 = std::get<2>(color) + std::get<2>(colorOne);

	return { value1, value2, value3 };
}

Vec3 operator*(float(&rotation)[3][3], const Vec3& dir) {
	float outputResult[3];
	float vec3array[3] = {dir.x, dir.y, dir.z};

	for (int i = 0; i < 3; ++i) {
		float total = 0;
		for (int j = 0; j < 3; ++j) {
			total += (vec3array[j]*rotation[i][j]);
		}
		outputResult[i] = total;
	}

	return Vec3(outputResult[0], outputResult[1], outputResult[2]);
}