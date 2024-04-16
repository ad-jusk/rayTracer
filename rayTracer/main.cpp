#include "test.hpp"
#include "camera/orthogonalCamera.hpp"
#include "camera/perspectiveCamera.hpp"
#include "light/pointLight.hpp"

int main() {
	
	// PREPARE PRIMITIVES
	std::vector<Primitive*> primitives;
	Primitive* p1 = new Sphere(Vector3(1.5f, 1.5, 10), 1.f, Material(MaterialType::Reflective, Vector3(.0f, .0f, .1f)));
	Primitive* p2 = new Sphere(Vector3(-1.5f, -1.5f, 9), 1.f, Material(MaterialType::Refractive, Vector3(0.f, 0.f, 0.f)));
	Primitive* p3 = new Sphere(Vector3(-1.f, -1.5f, 12), .5f, Material(MaterialType::Diffuse, Vector3(0.f, 0.f, 1.f)));
	Primitive* planeBack = new Plane(Vector3(0.f, 0.f, 1.f), 14.f, Material(MaterialType::Diffuse, Vector3(.9f, .0f, .75f)));
	Primitive* planeUp = new Plane(Vector3(0.f, 1.f, 0.f), 2.5f, Material(MaterialType::Diffuse, Vector3(1.f, 1.f, 1.f)));
	Primitive* planeBottom = new Plane(Vector3(0.f, -1.f, 0.f), 2.5f, Material(MaterialType::Diffuse, Vector3(0.f, 1.f, 0.f)));
	Primitive* planeRight = new Plane(Vector3(1.f, 0.f, 0.f), 2.5f, Material(MaterialType::Diffuse, Vector3(0.f, 0.f, 1.f)));
	Primitive* planeLeft = new Plane(Vector3(-1.f, 0.f, 0.f), 2.5f, Material(MaterialType::Diffuse, Vector3(1.f, 0.f, 0.f)));
	Primitive* planeFront = new Plane(Vector3(0.f,0.f,-1.f), 0.5f, Material(MaterialType::Diffuse, Vector3(1.f, 1.f, 0.f)));

	primitives.push_back(p1);
	primitives.push_back(p2);
	primitives.push_back(p3);
	primitives.push_back(planeUp);
	primitives.push_back(planeBottom);
	primitives.push_back(planeRight);
	primitives.push_back(planeLeft);
	primitives.push_back(planeBack);
	primitives.push_back(planeFront);

	// PREPARE LIGHTS
	std::vector<LightSource*> lights;
	LightSource* l1 = new PointLight(Vector3(0.f, 0.f, 12.), Vector3(1, 1, 1), 5.f);

	//LightSource* l2 = new PointLight(Vector3(0.f, 1.f, 12.), Vector3(1, 1, 1), 3.f);
	lights.push_back(l1);

	// RENDER ORTHOGONAL
	//OrthogonalCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 500, 500)
	//camera.renderScene(primitives);

	// RENDER PERSPECTIVE
	PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 500, 500, 40);
	camera.renderScene(primitives, lights, true);

	// DELETE ALLOCATED PRIMITIVES
	for (Primitive* p : primitives) {
		delete p;
	}

	// DELETE ALLOCATED LIGHTS
	for (LightSource* l : lights) {
		delete l;
	}
}