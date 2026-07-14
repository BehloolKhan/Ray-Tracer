#include "Scene.h"
#include "Sphere.h"
#include <vector>
#include "light.h"
#include "ChildLights.h"
#include <iostream>
#include <limits>
#include <cmath>

//method to compute the average of two extreme co-ordinates
//
float average(float x, float y) {
	return ((x+y)/2);
}

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

		//getting the reflectiveness of sphere
		//
		float reflection_;
		std::cout << "Enter reflective value - from 0.0 to 1.0";
		std::cin >> reflection_;

		spheres.push_back(Sphere(Vec3(x, y, z), radius, std::tuple<int, int, int>(R, G, B), specular_, reflection_));
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

void Scene::setBoundingCenter() {
	float x_min = std::numeric_limits<float>::infinity();
	float x_max = -std::numeric_limits<float>::infinity();

	float y_min = std::numeric_limits<float>::infinity();
	float y_max = -std::numeric_limits<float>::infinity();

	float z_min = std::numeric_limits<float>::infinity();
	float z_max = -std::numeric_limits<float>::infinity();

	for (int i = 0; i < spheres.size(); i++) {

		//setting the min next
		if (spheres.at(i).center.x < x_min) {
			x_min = spheres.at(i).center.x;
		}

		if (spheres.at(i).center.y < y_min) {
			y_min = spheres.at(i).center.y;
		}

		if (spheres.at(i).center.z < z_min) {
			z_min = spheres.at(i).center.z;
		}

		//setting the max next
		if (spheres.at(i).center.x > x_max) {
			x_max = spheres.at(i).center.x;
		}

		if (spheres.at(i).center.y > y_max) {
			y_max = spheres.at(i).center.y;
		}

		if (spheres.at(i).center.z > z_max) {
			z_max = spheres.at(i).center.z;
		}
	}

	center_public_sphere = Vec3(average(x_min, x_max), average(y_min, y_max), average(z_min, z_max));
}
void Scene::setBoundingRadius() {
	//assume we already have the center of the three spheres;
	//
	std::vector<float> distances;

	for (int i = 0; i < spheres.size(); ++i) {
		Vec3 sphereToCentre = spheres.at(i).center - center_public_sphere;
		distances.push_back(sphereToCentre.length() + spheres.at(i).radius);
	}

	//next we need to find the maximum of the distances
	//
	float max_radius = -std::numeric_limits<float>::infinity();
	for (int i = 0; i < spheres.size(); ++i) {
		if (spheres.at(i).radius > max_radius) {
			max_radius = spheres.at(i).radius;
		}
	}

	boundingSphereRadius = max_radius;
}

bool Scene::makeBoundingSphere() {

	if (!sphereCalculated) {
		setBoundingCenter();
		setBoundingRadius();
		sphereCalculated = true;
	}


	//first we need to do the ratio test
	//
	float total_vol_spheres = 0.0;
	for (int i = 0; i < spheres.size(); ++i) {
		total_vol_spheres += std::pow(spheres.at(i).radius, (float)3);
	}

	float total_vol_boundingSpheres = std::pow(boundingSphereRadius, (float)3);

	return ((total_vol_boundingSpheres / total_vol_spheres) <= 1.5);

}

float Scene::getBoundingSphereRadius() {
	return boundingSphereRadius;
}

Vec3& Scene::getBoundingSphereCentre() {
	return center_public_sphere;
}