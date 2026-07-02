//The file will include the constants used in this ray tracer
//
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Vec3.h"
#include <tuple>

inline constexpr float CANVAS_WIDTH = 200;
inline constexpr float CANVAS_HEIGHT = 200;

inline constexpr float VIEWPORT_HEIGHT = 1;
inline constexpr float VIEWPORT_WIDTH = 1;

inline constexpr int PROJECTTION_PLANE_D = 1;
inline Vec3 origin = Vec3(0, 0, 0);
inline std::tuple<int, int, int> BACKGROUND_COLOUR(0, 0, 0);

inline float rotationMatrix[3][3] = {
	{0.7071, 0.000, 0.7071},
	{-0.4082, 0.8165, 0.4082},
	{-0.5774, -0.5774, 0.5774} };
#endif