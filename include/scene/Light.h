//The light structure will be used to store information about lights
//
#ifndef LIGHT_H
#define LIGHT_H
#include <string>
#include "../core/Vec3.h"

class Light {
protected:
	std::string type;
	float intensity;
	void setIntensity(float intensity_);

public:

	Light(std::string type_, float intensity_);
	std::string getType() const ;
	float getIntensity() const;
	virtual ~Light() = default;

	virtual Vec3 getPosition();
	virtual Vec3 getDirection();
};
#endif