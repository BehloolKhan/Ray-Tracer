#include "boundingBox.h"

BoundingBox::BoundingBox():childSphere(nullptr) {
}

void BoundingBox::setChildSphere(Sphere* child_sphere) {
	this->childSphere = child_sphere;
}

void BoundingBox::set_min_max(Vec3 min_, Vec3 max_) {
	this->min = min_;
	this->max = max_;
}

Vec3& BoundingBox::getMax(){
	return max;
}

Vec3& BoundingBox::getMin(){
	return min;
}