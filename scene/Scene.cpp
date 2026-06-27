#include "Scene.h"
#include "Sphere.h"
#include <vector>
#include "light.h"
#include "ChildLights.h"
#include <iostream>

void Scene::setUpSpheres() {
	int numberSpheres;
	std::cout << "What is the number of spheres?: ";
	std::cin >> numberSpheres;

	for (int i = 1; i <= numberSpheres; ++i) {
		//grabbing co-ordinates
		//
		float x, y, z;
		std::cout << "Enter the x, y and z co-ordinates and use space to seperate them: ";

		std::cin >> x;
		std::cin >> y;
		std::cin >> z;

		//getting radius
		//
		float radius;
		std::cout << "Enter the radius of sphere " << i << ": ";
		std::cin >> radius;

		//getting the color values
		int R, G, B;
		std::cout << "Enter the format of the color in the form of R G B where each val between 0-255: ";
		std::cin >> R;
		std::cin >> G;
		std::cin >> B;

		//getting the specular value for spheres
		//
		int specular_;
		std::cout << "Enter the specular factor for given sphere";
		std::cin >> specular_;

		spheres.push_back(Sphere(Vec3(x, y, z), radius, std::tuple<int, int, int>(R, G, B), specular_));
	}
}

void Scene::setUpLights() {
	int numberLights;
	std::cout << "What is the number of point light sources and the number of different directional lights you have: ";
	std::cin >> numberLights;

	for (int i = 1; i <= numberLights; ++i) {
		//getting type
		//
		std::string type;
		std::cout << "Enter the type of light : point or directional: ";
		std::cin >> type;

		float intensity;
		std::cout << "Enter the intensity of point/directional light";
		std::cin >> intensity;

		float x, y, z; //co-ordinates used to store either direction of light or co-ordinates of source point of light

		if (type == "point") {
			//getting position of point light:
			//
			std::cout << "Enter the co-ordinates of the position of point light source and make sure to have a space between them: ";
		}
		else {
			//getting direction of unique directional light:
			//
			std::cout << "Enter the co-ordinates of the unique directional light: ";
		}

		std::cin >> x;
		std::cin >> y;
		std::cin >> z;

		if (type == "point") {
			Lights.push_back(new PointLight(type, intensity, Vec3(x, y, z)));
		}
		else {
			Lights.push_back(new DirectionalLight(type, intensity, Vec3(x, y, z)));
		}
	}

	float intensity;
	std::cout << "Enter the intensity of ambient light";
	std::cin >> intensity;

	Lights.push_back(new Light("ambient", intensity));
}

void Scene::setUpScene() {
	setUpSpheres();
	setUpLights();
}

std::vector<Sphere>& Scene::getSpheres() {
	return spheres;
}

std::vector<Light*>& Scene::getLights() {
	return Lights;
}