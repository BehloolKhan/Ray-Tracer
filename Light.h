//The light structure will be used to store information about lights
//
#ifndef LIGHT_H
#define LIGHT_H
#include <string>

struct Light {
protected:
	std::string type;
	float intensity;

public:
	Light(std::string type_, float intensity_);
	std::string getType();
	float getIntensity();
};
#endif