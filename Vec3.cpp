//This file will store the method defintions of the class Vec3
//
#include "Vec3.h"
#include <iostream>

Vec3::Vec3(float x_, float y_, float z_) {
	this->x = x_;
	this->y = y_;
	this->z = z_;
}

Vec3::Vec3() {
	x = 0;
	y = 0;
	z = 0;
}

Vec3 Vec3::operator+(const Vec3& otherVec3) const {
	return Vec3(this->x + otherVec3.x, this->y + otherVec3.y, this->z + otherVec3.z);
}

Vec3 Vec3::operator-(const Vec3& otherVec3) const {
	return Vec3(this->x - otherVec3.x, this->y - otherVec3.y, this->z - otherVec3.z);
}

float Vec3::dot(const Vec3& vec1, const Vec3& vec2) {
	return ((vec1.x*vec2.x) + (vec1.y*vec2.y) + (vec1.z*vec2.z));
}

void Vec3::printAll() {
	std::cout << "x: " << x << "y: " << y << "z: " << z << '\n';
}
