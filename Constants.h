//The file will include the constants used in this ray tracer
//
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Vec3.h"
#include <tuple>

float CANVAS_WIDTH = 500;
float CANVAS_HEIGHT = 500;

float VIEWPORT_HEIGHT = 1;
float VIEWPORT_WIDTH = 1;

int PROJECTTION_PLANE_D = 1;
Vec3 origin = Vec3(0, 0, 0);
std::tuple<int, int, int> BACKGROUND_COLOUR(255, 255, 255);
#endif