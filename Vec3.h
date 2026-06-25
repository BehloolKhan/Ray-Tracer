#ifndef VEC3_H
#define VEC3_H

struct Vec3 {

	float x;
	float y;
	float z;
	//constructor methods
	Vec3(float x_, float y_, float z_);
	Vec3();

	//addition one two vectors
	Vec3 operator+(const Vec3& otherVec3) const;

	//method that multiplies a scalar by a vector and returns answer;
	//
	static Vec3 multiplier(const Vec3& vec1, float factor);

	//method that devides a vector by a scalar and returns that
	//
	static Vec3 divides(const Vec3& vec1, float factor);

	//addition one two vectors
	Vec3 operator-(const Vec3& otherVec3) const;

	//returns the dot product of two vectors
	static float dot(const Vec3& vec1, const Vec3& vec2);


	//method prints all the values for a given
	void printAll();

	//method that returns the magnidute of a vector
	//
	float length() const;

	
};

#endif 