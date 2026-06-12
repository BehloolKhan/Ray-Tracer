#include <iostream>
#include "Constants.h"
#include "methods.h"
#include "Sphere.h"
#include "Vec3.h"
#include <tuple>
#include <limits>
#include <vector>

int main() {
	std::cout << "Hello World";

	//setting up the scene
	//
	std::vector<Sphere> Spheres = setUpScene();

	for (int x = -CANVAS_WIDTH / 2; x <= CANVAS_WIDTH / 2; ++x) {
		for (int y = -CANVAS_HEIGHT / 2; y <= CANVAS_HEIGHT / 2; ++y) {
			Vec3 V = canvasToViewPort(x, y);
			Vec3 D = V - origin;
			float posInf = std::numeric_limits<float>::infinity();
			std::tuple<int, int, int> color = TraceRay(origin, D, 1.0, posInf, Spheres);
		}
	}
}