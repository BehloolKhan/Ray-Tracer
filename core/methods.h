//header file containg method declerations
//
#ifndef METHODS_H
#define METHODS_H

#include <tuple>
#include "Vec3.h"
#include "../scene/Sphere.h"
#include <vector>
#include "../scene/Scene.h"

//method returns the two t values where a ray interserct a given sphere if it does so
//if ray doesnt interesect sphere, infinity is returned
//
std::tuple<float, float> IntersectRaySphere(Vec3& O_, Vec3& D, Sphere sphere);

//method computes the intersection of the ray with every sphere
//returns the color of the sphere at the nearest interaction inside range
//
std::tuple<int, int, int>TraceRay(Vec3& O_, Vec3& D, float t_min, float t_max, Scene& scene, int recursionDepth);

//method to return the correponding point on the view port for a given canvas
//
Vec3 canvasToViewPort(int x, int y);

//method that calculates the intensity at a given point P
//
float computeLighting(Vec3& O, Vec3& P, Vec3& N, Scene& scene, int specular);

//method that allows us to muliply a color vector by a number
//
void multiplyColorVector(std::tuple<int, int, int>& color, float factor);

//method that adds two color vectors together
//
std::tuple<int, int, int> addTwoColors(std::tuple<int, int, int>& color, std::tuple<int, int, int>& colorOne);

//method that extracts the closesest intersection of the TraceRay part method so it can be reused;
//
std::tuple<Sphere*, float>closestIntersection(Vec3& O, Vec3& direction_, float t_min, float t_max, Scene& scene);

//method, given a ray returns the reflective ray with respect to normal
//
Vec3 reflectRay(Vec3& R, Vec3&N);

//method multiplies a One dimensional vector by a 3D rotation matrix
//
Vec3 operator*(float (&rotation)[3][3], const Vec3&dir);
#endif