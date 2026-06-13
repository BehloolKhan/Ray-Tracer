//This will include the function/procedure definitons for all the functions/procedures used in the book
//

#include "Constants.h"
#include "Vec3.h"
#include <tuple>
#include "Sphere.h"
#include <limits>
#include <cmath>
#include <vector>
#include <iostream>

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

std::tuple<int, int, int> TraceRay(Vec3& O, Vec3& D, float t_min, float t_max, std::vector<Sphere>& Spheres) {
	float closest_t = std::numeric_limits<float>::infinity();
	Sphere* closest_sphere = nullptr;

	for (Sphere& currentSphere : Spheres) {

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

		std::cout << "if-conditions for ts finished:";
	}

	if (closest_sphere == nullptr) {
		return BACKGROUND_COLOUR;
	}

	std::cout << "intersection happened\n";

	std::tuple<int, int, int> color = closest_sphere->color;

	std::cout << "color being accessed";

	closest_sphere = nullptr;

	std::cout << "color is returned";

	return color;
}

std::vector<Sphere> setUpScene() {
	std::vector<Sphere> spheres;
	int numberSpheres;
	std::cout << "What is the number of spheres?: ";
	std::cin >> numberSpheres;

	for (int i = 1; i <= numberSpheres; ++i) {
		//grabbing co-ordinates
		//
		float x, y, z;
		std::cout << "Enter the x, y and z co-ordinates and use space to seperate them: ";

		std::cin >> x;
		std::cin >> y;
		std::cin >> z;

		//getting radius
		//
		float radius;
		std::cout << "Enter the radius of sphere " << i << ": ";
		std::cin >> radius;

		//getting the color values
		int R, G, B;
		std::cout << "Enter the format of the color in the form of R G B where each val between 0-255: ";
		std::cin >> R;
		std::cin >> G;
		std::cin >> B;

		spheres.push_back(Sphere(Vec3(x, y, z), radius, std::tuple<int, int, int>(R, G, B)));
	}

	return spheres;
}