#include "Light.h"
#include <string>


Light::Light(std::string type_, float intensity_) {
	this->type = type_;
	setIntensity(intensity_);
}

std::string Light::getType() const{
	return type;
}

float Light::getIntensity() const{
	return intensity;
}

void Light::setIntensity(float intensity_) {
	if (intensity_ > 1.0) {
		this->intensity = 1.0;
	}
	else if (intensity < 0.0) {
		this->intensity = 0.0;
	}

	this->intensity = intensity_;
}

Vec3 Light::getPosition() {
	return Vec3(0, 0, 0);
}

Vec3 Light::getDirection() {
	return Vec3(0, 0, 0);
}