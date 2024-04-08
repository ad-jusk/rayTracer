#include "test.hpp"
#include "camera/orthogonalCamera.hpp"
#include "camera/perspectiveCamera.hpp"
#include "light/pointLight.hpp"

int main() {
	
	// PREPARE PRIMITIVES
	std::vector<Primitive*> primitives;
	Primitive* p1 = new Sphere(Vector3(1.3f, 0, 8), 1.5f, Material(Vector3(.2f, .4f, .75f)));
	Primitive* p2 = new Sphere(Vector3(-1.0f, 0.5f, 10), 1.f, Material(Vector3(.8f, .1f, .45f)));
	primitives.push_back(p1);
	primitives.push_back(p2);

	// PREPARE LIGHTS
	std::vector<LightSource*> lights;
	LightSource* l1 = new PointLight(Vector3(0.5f, -0.8f, 4.5), Vector3(1, 1, 1), 2.f);
	lights.push_back(l1);

	// RENDER ORTHOGONAL
	//OrthogonalCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 500, 500);
	//camera.renderScene(primitives);

	// RENDER PERSPECTIVE
	PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 500, 500, 60);
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