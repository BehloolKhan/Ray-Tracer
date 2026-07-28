//The data structur in this file will be used to store information about the spheres collected
//

#ifndef LIST_SPHERES_H
#define LIST_SPHERES_H

#include <vector>
#include "Sphere.h"
#include <limits>
#include "BoundingTree.h"
#include <span>


struct ListSpheres {

	std::vector<Sphere> spheres;

	//max-dimension
	// 
	char max_dimension;

	BoundingTree boundingTree;

	/************/

	//returns the maximum and minimum co-ordinates of a data
	//
	Vec3* setBoundingBox(std::span<Sphere>data);

	//sets the axis of which the range is the greatest
	//
	void setTheMaxDimension();

	//sorting the list of the spheres in order of max_dimesnion
	//
	void sort();

	//next we need to recursively divide the list
	//into left and right
	//call the method on left and then right
	//base case: left or right length is equal to 1:
	void setBoundingTree(std::span<Sphere>data, BoundingTree& currentBoundingTree, int start_index, int count);

	//method returns true if a ray intersect an AABB - Axis Aligned Bounding Box
	//
	bool rayIntersectAABB(const Vec3& P, const Vec3& D, BoundingBox& AABB);

	//method lowkey helps in the above method - does a part of it
	//
	float calculate_t(float B_x, float P_x, float D_x);

	//calculates the minimum of three values
	//
	float min(float t1, float t2, float t3);

	//calculates the maximum of the three values
	//
	float max(float t1, float t2, float t3);
};

#endif LIST_SPHERES_H