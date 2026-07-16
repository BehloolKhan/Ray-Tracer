// This header file will be used to store the structure of a tree
// a Tree consists of a root node associated with a value and a left and right subtree
//
#include <memory>
#include "boundingBox.h"

class BoundingTree {

	BoundingBox rootNode;

	BoundingTree(BoundingBox rootNode); 

	std::unique_ptr<BoundingTree> leftTree;
	std::unique_ptr<BoundingTree> rightTree;

	void setLeftChild(BoundingTree* leftTree_);
	void setRightChild(BoundingTree* rightTree_);
};