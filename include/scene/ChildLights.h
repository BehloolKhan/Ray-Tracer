//This file contains the structs - child ones of the parent class - Light which add on
//an additional attribute - position of light or direcyion of light
//
#ifndef CHILD_LIGHTS_H
#define CHILD_LIGHTS_H
#include <string>
#include "Light.h"
#include "../core/Vec3.h"

class PointLight: public Light {

private:
	Vec3 position;

public:
	PointLight(std::string type_, float intensity_, const Vec3& position_);
	Vec3 getPosition();
};

class DirectionalLight : public Light {

private:
	Vec3 direction;

public:
	DirectionalLight(std::string type_, float intensity_, const Vec3& direction_);
	Vec3 getDirection();
};
#endif