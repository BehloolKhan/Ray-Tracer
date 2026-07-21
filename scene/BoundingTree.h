// This header file will be used to store the structure of a tree
// a Tree consists of a root node associated with a value and a left and right subtree
//
#include <memory>
#include "boundingBox.h"

class BoundingTree {

private:
	BoundingBox rootNode;

	std::unique_ptr<BoundingTree> leftTree;
	std::unique_ptr<BoundingTree> rightTree;

public:
	void setLeftChild(BoundingTree* leftTree_);
	void setRightChild(BoundingTree* rightTree_);

	BoundingTree* getLeftChild() const;
	BoundingTree* getRightChild() const;

	//method that adjusts the dimesnions of root node bounding box
	//
	void setRootNode(Vec3 new_min, Vec3 new_max);

	//returns a reference to the rootNode
	//
	BoundingBox& getRootNode();
};