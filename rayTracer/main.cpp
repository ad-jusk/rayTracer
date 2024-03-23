#include "include/test.hpp"
#include "include/camera/orthogonalCamera.hpp"
#include "include/camera/perspectiveCamera.hpp"

int main() {
	
	// PREPARE PRIMITIVES
	std::vector<Primitive*> primitives;
	Primitive* p1 = new Sphere(Vector3(1, 0, 7), 0.7f);
	Primitive* p2 = new Sphere(Vector3(0, 0, 7), 1.0f, Vector3(0, 0, 1));
	primitives.push_back(p1);
	primitives.push_back(p2);

	// RENDER ORTHOGONAL
	OrthogonalCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 500, 500);
	camera.renderScene(primitives);

	// RENDER PERSPECTIVE
	//PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 500, 500, 60);
	//camera.renderScene(primitives, true);

	// DELETE ALLOCATED PRIMITIVES
	for (Primitive* p : primitives) {
		delete p;
	}
}