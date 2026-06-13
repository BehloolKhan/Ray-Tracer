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


	//addition one two vectors
	Vec3 operator-(const Vec3& otherVec3) const;

	//returns the dot product of two vectors
	static float dot(const Vec3& vec1, const Vec3& vec2);

	//method prints all the values for a given
	void printAll();


};

#endif 