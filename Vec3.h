#ifndef VEC3_H
#define VEC3_H


struct Vec3 {

	float x;
	float y;
	float z;

	Vec3(float x_, float y_, float z_) {
		this->x = x_;
		this->y = y_;
		this->z = z_;
	}

	//default constructor
	//
	Vec3() {
		x = 0;
		y = 0;
		z = 0;
	}
};

#endif 