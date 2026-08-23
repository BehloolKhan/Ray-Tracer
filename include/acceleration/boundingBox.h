//This file will also be used to store the information about a bounding box
//

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "..\core\Vec3.h"
#include "..\geometry\Sphere.h"

class BoundingBox {
	Vec3 min; //used to store the min (x,y,z) co-ordinate 
	Vec3 max; //used to store the max (x,y,z) co-ordinate 
	Sphere childSphere;  //store reference to the child node it it can, if null - then not leaf node
	bool isChildNode;

public:
	BoundingBox();
	void setChildSphere(Sphere child_sphere);

	void set_min_max(Vec3 min_, Vec3 max_);

	Vec3& getMin() ;

	Vec3& getMax();

	Sphere& getChildSphere();

	void setChild(bool isChild);

	bool isChild();


};

#endif