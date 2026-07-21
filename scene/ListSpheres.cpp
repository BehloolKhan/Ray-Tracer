#include "ListSpheres.h"
#include <algorithm>
#include "Sphere.h"

Vec3* ListSpheres::setBoundingBox(std::span<Sphere>data) {

	float infinity = std::numeric_limits<float>::infinity();

	float x_min = infinity, y_min = infinity, z_min = infinity;
	float x_max = -infinity, y_max = -infinity, z_max = -infinity;

	for (Sphere& element : data) {

		//setting the min values
		//
		if (element.center.x < x_min) {
			x_min = element.center.x;
		}

		if (element.center.y < y_min) {
			y_min = element.center.y;
		}

		if (element.center.z < z_min) {
			z_min = element.center.z;
		}

		//setting the max values
		//
		if (element.center.x > x_max) {
			x_max = element.center.x;
		}

		if (element.center.y > y_max) {
			y_max = element.center.y;
		}

		if (element.center.x > z_max) {
			z_max = element.center.z;
		}
	}

	//set the dimensions of the bounding box inside the root node;
	//
	Vec3* result = new Vec3[2]{ Vec3(x_min, y_min, z_min), Vec3(x_max, y_max, z_max) };
	return result;


}

void ListSpheres::setTheMaxDimension() {

	Vec3* results = setBoundingBox(spheres);

	float x_range = results[1].x - results[0].x;
	float y_range = results[1].y - results[0].y;
	float z_range = results[1].z - results[0].z;

	if (x_range > y_range) {
		if (x_range > z_range) {
			max_dimension = 'x';
		}

		else {
			max_dimension = 'z';
		}
	}

	else {
		if (y_range > z_range) {
			max_dimension = 'y';
		}

		else {
			max_dimension = 'z';
		}
	}

	delete[] results;
	results = nullptr;
};

//comparison rule:
bool compareX(Sphere& A, Sphere& B) {
	if (A.center.x < B.center.x) {
		return true;
	}
	
	return false;
}

bool compareY(Sphere& A, Sphere& B) {
	if (A.center.y < B.center.y) {
		return true;
	}

	return false;
}

bool compareZ(Sphere& A, Sphere& B) {
	if (A.center.z < B.center.z) {
		return true;
	}

	return false;
}

void ListSpheres::sort() {
	if (max_dimension == 'x') {
		std::sort(spheres.begin(), spheres.end(), compareX);
	}

	else if (max_dimension == 'y') {
		std::sort(spheres.begin(), spheres.end(), compareY);
	}

	else if (max_dimension == 'z') {
		std::sort(spheres.begin(), spheres.end(), compareZ);
	}
}

void ListSpheres::setBoundingTree(std::span<Sphere>data, BoundingTree& currentBoundingTree, int start_index, int count) {
	//terminate if count is equal to one
	//
	if (count == 1) {
		currentBoundingTree.getRootNode().setChildSphere(&data[start_index]);
		return; //exit the function
	}

	//calculate the max and min co-ordinates for spheres in data
	//set the root node of current bounding Tree
	Vec3* coordinates = setBoundingBox(data);
	currentBoundingTree.setRootNode(coordinates[0], coordinates[1]);

	//split vector into two parts
	//
	int left_size = count / 2;
	int right_size = count - left_size;

	//need to create two new boundingTrees, assign them to the left and right of current bounding Tree
	//

	currentBoundingTree.setLeftChild(new BoundingTree());
	currentBoundingTree.setRightChild(new BoundingTree());

	setBoundingTree(data.subspan(start_index, left_size), *(currentBoundingTree.getLeftChild()), 0, left_size);
	setBoundingTree(data.subspan(start_index+left_size, right_size), *(currentBoundingTree.getRightChild()), 0, right_size);
	
};