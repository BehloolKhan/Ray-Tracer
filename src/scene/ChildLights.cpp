#include "ChildLights.h"
#include "Light.h"
#include "../core/Vec3.h"

PointLight::PointLight(std::string type_, float intensity_, const Vec3& position_) : Light(type_, intensity_) {
	this->position = position_;
}

Vec3 PointLight::getPosition() {
	return this->position;
}

DirectionalLight::DirectionalLight(std::string type_, float intensity_, const Vec3& direction_) : Light(type_, intensity_) {
	this->direction = direction_;
}

Vec3 DirectionalLight::getDirection() {
	return this->direction;
}