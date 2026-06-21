//This header file contains the code for the cpp class
#ifndef SCENE_H
#define SCENE_H

#include "Sphere.h"
#include <vector>
#include "light.h"
#include "ChildLights.h"

class Scene {
private:
	std::vector<Sphere> spheres;
	std::vector<Light*> Lights;

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
};
#endif