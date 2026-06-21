#include "Light.h"
#include <string>

Light::Light(std::string type_, float intensity_) {
	this->type = type_;
	this->intensity = intensity_;
}

std::string Light::getType() {
	return type;
}

float Light::getIntensity() {
	return intensity;
}