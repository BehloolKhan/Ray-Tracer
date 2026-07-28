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

bool ListSpheres::rayIntersectAABB(const Vec3& P, const Vec3& D, BoundingBox& AABB) {
	float t_min_x = calculate_t(AABB.getMin().x, P.x, D.x);
	float t_max_x = calculate_t(AABB.getMax().x, P.x, D.x);

	float t_min_y = calculate_t(AABB.getMin().y, P.y, D.y);
	float t_max_y = calculate_t(AABB.getMax().y, P.y, D.y);

	float t_min_z = calculate_t(AABB.getMin().z, P.z, D.z);
	float t_max_z = calculate_t(AABB.getMax().z, P.z, D.z);

	if (t_min_x > t_max_x) {
		float t_current = t_min_x;
		t_min_x = t_max_x;
		t_max_x = t_current;
	}

	if (t_min_y > t_max_y) {
		float t_current = t_min_y;
		t_min_y = t_max_y;
		t_max_y = t_current;
	}

	if (t_min_z > t_max_z) {
		float t_current = t_min_z;
		t_min_z = t_max_z;
		t_max_z = t_current;
	}

	float t_near = max(t_min_x, t_min_y, t_min_z);
	float t_far = min(t_max_x, t_max_y, t_max_z);

	if (t_near > t_far) {
		return false; //not intersected box at all
	}

	if (t_far < 0) {
		return false; //box behind 
	}

	return true;
};

float ListSpheres::calculate_t(float B_x, float P_x, float D_x) {
	return (B_x - P_x) / D_x;
};

float ListSpheres::min(float t1, float t2, float t3) {
	if (t1 < t2) {
		if (t1 < t3) {
			return t1;
		}
		else {
			return t3;
		}
	}
	else {
		if (t2 < t3) {
			return t2;
		}
		else {
			return t3;
		}
	}
};

float ListSpheres::max(float t1, float t2, float t3) {
	if (t1 > t2) {
		if (t1 > t3) {
			return t1;
		}
		else {
			return t3;
		}
	}
	else {
		if (t2 > t3) {
			return t2;
		}
		else {
			return t3;
		}
	}
};