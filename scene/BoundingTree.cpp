#include "BoundingTree.h"

void BoundingTree::setLeftChild(BoundingTree* leftTree_) {
	leftTree = std::unique_ptr<BoundingTree>(leftTree_);
}

void BoundingTree::setRightChild(BoundingTree* rightTree_) {
	rightTree = std::unique_ptr<BoundingTree>(rightTree_);
}

void BoundingTree::setRootNode(Vec3 new_min, Vec3 new_max) {

	rootNode.set_min_max(new_min, new_max); //call the constructor again

}

BoundingBox& BoundingTree::getRootNode() {
	return rootNode; //
}

BoundingTree* BoundingTree::getLeftChild() const{
	return leftTree.get();
}

BoundingTree* BoundingTree::getRightChild() const {
	return rightTree.get();
}