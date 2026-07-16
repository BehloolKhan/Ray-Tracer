//This file will also be used to store the information about a bounding box
//
#include "..\core\Vec3.h";
class BoundingBox {
	Vec3 min; //used to store the min (x,y,z) co-ordinate 
	Vec3 max; //used to store the max (x,y,z) co-ordinate 

public:
	BoundingBox(Vec3 min_, Vec3 max_);
};