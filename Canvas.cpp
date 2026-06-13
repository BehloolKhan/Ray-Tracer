#include "Canvas.h"
#include <fstream>
#include <tuple>
#include "Constants.h"

Canvas::Canvas() {

};

void Canvas::putPixel(int x, int y, std::tuple<int, int, int>& color) {
	//needt to convert x,y -> standard original x, y co-ordinates:
	//
	int S_X = ((int)CANVAS_WIDTH) / 2 + x;
	int S_Y = (((int)CANVAS_HEIGHT) / 2) -1 - y;
	//Now I need to flatten the two-dimensional co-ordinates two a one dimesnional index
	//
	int index = (S_Y * ((int)CANVAS_WIDTH)) + S_X;
	colors[index] = color;
}

void Canvas::writeToFile() {

	imageFile = std::ofstream("imageFile.ppm");
	//writing the dimensions and format
	imageFile << "P3" << '\n' << (int)CANVAS_WIDTH << " " << (int)CANVAS_WIDTH << '\n' << 255 << '\n';

	//getting all the colors and write it to the file
	//
	int total = ((int)CANVAS_WIDTH) * ((int)CANVAS_HEIGHT);
	for (int i = 0; i < total; ++i) {
		std::tuple <int, int, int>& current_colour = colors[i];
		imageFile << std::get<0>(current_colour) << " " << std::get<1>(current_colour) << " " << std::get<2>(current_colour) << '\n';
	}

	imageFile.close();
}

Canvas::~Canvas() {
	//need to free the memory from array
	//
	delete[] colors;
	colors = nullptr;
}