#include <iostream>
#include "core/Constants.h"
#include "core/methods.h"
#include "scene/Sphere.h"
#include "core/Vec3.h"
#include <tuple>
#include <limits>
#include <vector>
#include "core/Canvas.h"
#include "scene/Scene.h"

int main() {
	std::cout << "Hello World" << '\n';

	//setting up the scene
	//
	Scene scene{};
	Canvas canvas{}; //use curly brace to initialise Canvas object;

	scene.setUpScene(); //get the information we need;

	for (int x = -CANVAS_WIDTH / 2; x < CANVAS_WIDTH / 2; ++x) {
		for (int y = -CANVAS_HEIGHT / 2; y < CANVAS_HEIGHT / 2; ++y) {
			Vec3 V = canvasToViewPort(x, y);
			Vec3 D = V - origin;
			float posInf = std::numeric_limits<float>::infinity();
			std::tuple<int, int, int> color = TraceRay(origin, D, 1.0, posInf, scene, 3);
			canvas.putPixel(x, y, color);
		}
	}
	canvas.writeToFile();
}