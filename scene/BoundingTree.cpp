#include "BoundingTree.h"

BoundingTree::BoundingTree(BoundingBox root_Node): rootNode(root_Node){

}

void BoundingTree::setLeftChild(BoundingTree* leftTree_) {
	leftTree = std::unique_ptr<BoundingTree>(leftTree_);
}

void BoundingTree::setRightChild(BoundingTree* rightTree_) {
	rightTree = std::unique_ptr<BoundingTree>(rightTree_);
}

