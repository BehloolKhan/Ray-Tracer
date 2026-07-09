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
#include <thread>

void partOfCanvas(int start_X, int end_X, Scene& scene, Canvas& canvas) {

	for (int x = start_X; x < end_X; ++x) {
		for (int y = -CANVAS_HEIGHT / 2; y < CANVAS_HEIGHT / 2; ++y) {
			Vec3 V = canvasToViewPort(x, y);
			Vec3 D = rotationMatrix * V;
			float posInf = std::numeric_limits<float>::infinity();
			std::tuple<int, int, int> color = TraceRay(origin, D, 1.0, posInf, scene, 3);
			canvas.putPixel(x, y, color);
		}
	}
}

int main() {
	std::cout << "Hello World" << '\n';

	//setting up the scene
	//
	Scene scene{};
	Canvas canvas{}; //use curly brace to initialise Canvas object;

	scene.setUpScene(); //get the information we need;
	unsigned int num_threads = std::thread::hardware_concurrency();
	if (num_threads == 0) {
		num_threads = 2;
	}

	std::vector<std::thread> vectorThreads;

	int chunk = (int)(CANVAS_WIDTH/ num_threads);
	int start_X = -CANVAS_WIDTH / 2;

	//creating threads
	for (int i = 1; i <= num_threads; ++i) {
		vectorThreads.push_back( std::thread(partOfCanvas, start_X, start_X+chunk, std::ref(scene), std::ref(canvas)) );
		start_X += chunk;
	}

	if (start_X < ((int)CANVAS_WIDTH / 2)) {
		vectorThreads.push_back( std::thread(partOfCanvas, start_X, (int)CANVAS_WIDTH / 2, std::ref(scene), std::ref(canvas)) );
	}

	//joining threads
	for (std::thread& item : vectorThreads) {
		item.join();
	}

	canvas.writeToFile();
}