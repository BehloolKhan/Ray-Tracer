#ifndef CANVAS_H
#define CANVAS_H
#include <fstream>
#include <tuple>
#include "Constants.h"

class Canvas {
public:
	//constructor
	Canvas();
	void putPixel(int x, int y, std::tuple<int, int, int>& color);
	void writeToFile();
	~Canvas();

private:
	std::ofstream imageFile;
	std::tuple<int, int, int>* colors = new std::tuple<int, int, int>[(int)CANVAS_WIDTH * (int)CANVAS_HEIGHT];
};
#endif 