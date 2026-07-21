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
};

#endif LIST_SPHERES_H