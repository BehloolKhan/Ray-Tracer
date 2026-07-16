//This header file contains the code for the cpp class
#ifndef SCENE_H
#define SCENE_H

#include "Sphere.h"
#include <vector>
#include "light.h"
#include "ChildLights.h"
#include "../core/Vec3.h"
#include "BoundingTree.h"

class Scene {
private:
	std::vector<Sphere> spheres;
	std::vector<Light*> Lights;
	Vec3 center_public_sphere;
	float boundingSphereRadius;
	bool sphereCalculated = false; // this it to keep track of weather or not the bounding sphere dimesnions have already been calculated
	char BoundingAxis;

	BoundingTree BoundingSpheres;

public:
	//method that sets up the spheres in the scene+
	//
	void setUpSpheres();
	//method sets up the light sources in the scene
	//
	void setUpLights();
	//method is responsible for setting up all
	//the lights and spheres in scene
	//
	void setUpScene();
	//method is responsible for returing spheres
	//
	std::vector<Sphere>& getSpheres();

	//method is responsible for returning lights
	//
	std::vector<Light*>& getLights();

	//method that sets out the center of the bounding sphere
	//
	void setBoundingCenter();

	//method to set the radius of the bounding sphere - center and radius
	//
	void setBoundingRadius();

	//method that calculate weather we should procede with the bounding sphere
	//
	bool makeBoundingSphere();

	//method that returns boundingSphere radius
	//
	float getBoundingSphereRadius();

	//method that returns the center of the bounding sphere
	//
	Vec3& getBoundingSphereCentre();

	//method that will set up the bounding boxes;
	//
	void setUpBoundingTree();


};
#endif