#include "ListSpheres.h"
#include <algorithm>
#include "Sphere.h"
#include "../core/methods.h"


Vec3* ListSpheres::setBoundingBox(std::span<Sphere>data) {

	float infinity = std::numeric_limits<float>::infinity();

	float x_min = infinity, y_min = infinity, z_min = infinity;
	float x_max = -infinity, y_max = -infinity, z_max = -infinity;

	for (Sphere& element : data) {

		//setting the min values
		//
		if (element.center.x - element.radius < x_min) {
			x_min = element.center.x - element.radius;
		}

		if (element.center.y - element.radius< y_min) {
			y_min = element.center.y - element.radius;
		}

		if (element.center.z - element.radius < z_min) {
			z_min = element.center.z - element.radius;
		}

		//setting the max values
		//
		if (element.center.x + element.radius> x_max) {
			x_max = element.center.x + element.radius;
		}

		if (element.center.y + element.radius> y_max) {
			y_max = element.center.y + element.radius;
		}

		if (element.center.z + element.radius> z_max) {
			z_max = element.center.z + element.radius;
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

	//calculate the max and min co-ordinates for spheres in data
	//set the root node of current bounding Tree
	Vec3* coordinates = setBoundingBox(data);
	currentBoundingTree.setRootNode(coordinates[0], coordinates[1]);

	//terminate if count is equal to one
	//
	if (count == 1) {
		currentBoundingTree.getRootNode().setChildSphere(data[start_index]);
		currentBoundingTree.getRootNode().setChild(true);
		return; //exit the function
	}

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
	float t_min = -std::numeric_limits<float>::infinity();
	float t_max = std::numeric_limits<float>::infinity();

	// Check X axis
	if (std::abs(D.x) < 1e-6f) { // Ray is parallel to slab
		if (P.x < AABB.getMin().x || P.x > AABB.getMax().x) return false;
	}
	else {
		float invD = 1.0f / D.x;
		float t1 = (AABB.getMin().x - P.x) * invD;
		float t2 = (AABB.getMax().x - P.x) * invD;

		if (t1 > t2) std::swap(t1, t2);

		t_min = std::max(t_min, t1);
		t_max = std::min(t_max, t2);

		if (t_min > t_max) return false;
	}

	// Check Y axis
	if (std::abs(D.y) < 1e-6f) {
		if (P.y < AABB.getMin().y || P.y > AABB.getMax().y) return false;
	}
	else {
		float invD = 1.0f / D.y;
		float t1 = (AABB.getMin().y - P.y) * invD;
		float t2 = (AABB.getMax().y - P.y) * invD;

		if (t1 > t2) std::swap(t1, t2);

		t_min = std::max(t_min, t1);
		t_max = std::min(t_max, t2);

		if (t_min > t_max) return false;
	}

	// Check Z axis
	if (std::abs(D.z) < 1e-6f) {
		if (P.z < AABB.getMin().z || P.z > AABB.getMax().z) return false;
	}
	else {
		float invD = 1.0f / D.z;
		float t1 = (AABB.getMin().z - P.z) * invD;
		float t2 = (AABB.getMax().z - P.z) * invD;

		if (t1 > t2) std::swap(t1, t2);

		t_min = std::max(t_min, t1);
		t_max = std::min(t_max, t2);

		if (t_min > t_max) return false;
	}

	return t_max >= 0.0f; // Ensure box is not behind the ray origin
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

std::tuple<Sphere, float> ListSpheres::closestSphere(Vec3& P, Vec3& D, float t_min, float t_max, BoundingTree& currentBoundingTree) {
	//intersect box in BoundingTree
	// If empty node or the ray misses this node's bounding box completely, return no hit
	//
	if (!rayIntersectAABB(P, D, currentBoundingTree.getRootNode())) {
		return { Sphere(), t_max};
	}

	// Leaf node check: childSphere pointer is valid (not nullptr) - checking to see if the root node of the currentBoundingTree is not a root node
	//
	Sphere sphere = currentBoundingTree.getRootNode().getChildSphere();
	bool isChild = currentBoundingTree.getRootNode().isChild();

	if (isChild) {
		// Test intersection with actual geometry inside the leaf
		float closest_t = t_max;
		std::tuple<float, float>results = IntersectRaySphere(P, D, sphere);

		float t1 = std::get<0>(results);
		float t2 = std::get<1>(results);

		if (((t1 >= t_min) && (t1 < t_max)) && t1 < closest_t) {
			closest_t = t1;

		}

		if (((t2 >= t_min) && (t2 < t_max)) && t2 < closest_t) {
			closest_t = t2;

		}
		return {sphere, closest_t};
	}

	// Internal node: Recurse into both left and right children
	Sphere closest_sphere{};
	float current_closest_t = t_max;

	// Check left subtree
	auto [left_sphere, left_t] = closestSphere(P, D, t_min, current_closest_t, (*currentBoundingTree.getLeftChild()));
	if (left_t < current_closest_t) {
		closest_sphere = left_sphere;
		current_closest_t = left_t; // Tighten t_max so right child can prune further
	}

	// Check right subtree with updated (possibly smaller) max distance
	auto [right_sphere, right_t] = closestSphere(P, D, t_min, current_closest_t, (*currentBoundingTree.getRightChild()));
	if (right_t < current_closest_t) {
		closest_sphere = right_sphere;
		current_closest_t = right_t;
	}

	return { closest_sphere, current_closest_t };
	
}

BoundingTree& ListSpheres::getBoundingTree() {
	return boundingTree;
}