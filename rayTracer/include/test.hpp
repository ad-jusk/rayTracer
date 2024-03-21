#pragma once

#include "sphere.hpp"
#include "plane.hpp"
#include "triangle.hpp"

void testVector() {

	std::cout << std::endl  << "### VECTOR TESTS ###" << std::endl;

	Vector3 v1(0, 3, 0);
	Vector3 v2(5, 5, 0);

	std::cout << "Sum of " << v1 << " and " << v2 << ": " << v1 + v2 << std::endl;
	std::cout << "Subtraction of " << v1 << " from " << v2 << ": " << v2 - v1 << std::endl;
	std::cout << "Multiplication of " << v1 << " by 2: " << v1 * 2 << std::endl;
	std::cout << "Division of " << v1 << " by 2: " << v1 / 2 << std::endl;
	std::cout << "Angle between " << v1 << " and " << v2 << ": " << v1.angle(v2) << std::endl;
	std::cout << "Cross product of " << v1 << " and " << v2 << ": " << v1.cross(v2) << std::endl;
	std::cout << "Multiplication of " << v1 << " and " << v2 << ": " << v1 * v2 << std::endl;
	std::cout << "Normalized vector " << v2 << ": " << v2.normalize() << std::endl;

}
 
void testRay() {

	std::cout << std::endl << "### RAY TESTS ###" << std::endl;

	Vector3 p1(1, 2, 3);
	Vector3 p2(4, 5, 6);
	Vector3 p3(15, 19.5, 24);
	Vector3 p4(-3, -3, -3);

	Ray ray(p1, p2);

	std::cout << "Ray: " << ray << std::endl;

	bool result1 = ray.isPointOnRay(p1);
	bool result2 = ray.isPointOnRay(p2);
	bool result3 = ray.isPointOnRay(p3);
	bool result4 = ray.isPointOnRay(p4);

	if (result1) {
		std::cout << p1 << " is on ray - OK" << std::endl;
	}
	else {
		std::cout << p1 << " is not on ray but should be" << std::endl;
	}

	if (result2) {
		std::cout << p2 << " is on ray but shouldn't be" << std::endl;
	}
	else {
		std::cout << p2 << " is not on ray - OK" << std::endl;
	}

	if (result3) {
		std::cout << p3 << " is on ray - OK" << std::endl;
	}
	else {
		std::cout << p3 << " is not on ray but should be" << std::endl;
	}

	if (result4) {
		std::cout << p4 <<  " is on ray but shouldn't be" << std::endl;
	}
	else {
		std::cout << p4 << " is not on ray - OK" << std::endl;
	}
}

void testSphere() {

	std::cout << std::endl << "### SPHERE TESTS ###" << std::endl;

	Vector3 sphereCenter(0, 0, 0);
	Sphere s1(sphereCenter, 10);

	Vector3 origin(0, 0, -20);
	Vector3 direction1(0, 0, 1);
	Vector3 direction2(0, 1, 0);

	Ray r1(origin, direction1);
	Ray r2(origin, direction2);

	std::cout << "Sphere: " << s1 << std::endl;
	std::cout << "Ray 1: " << r1 << std::endl;
	std::cout << "Ray 2: " << r2 << std::endl;

	IntersectionInfo info1 = s1.getRayIntersection(r1);
	IntersectionInfo info2 = s1.getRayIntersection(r2);

	std::cout << info1 << std::endl;
	std::cout << info2 << std::endl;
}

void testPlane() {
	
	std::cout << std::endl << "### PLANE TESTS ###" << std::endl;

	Vector3 v1(0, 0, -20);
	Vector3 v2(0, 1, 0);
	Vector3 v3(0, 1, 1);

	Plane p1(v3, 0);

	std::cout << p1 << std::endl;

	Ray r1(v1, v2);

	std::cout << r1 << std::endl;

	IntersectionInfo info = p1.getRayIntersection(r1);

	std::cout << info << std::endl;
}

void testTriangle() {

	std::cout << std::endl << "### TRIANGLE TESTS ###" << std::endl;

	Vector3 v1(0, 0, 0);
	Vector3 v2(1, 0, 0);
	Vector3 v3(0, 1, 0);

	Triangle t(v1, v2, v3);

	std::cout << t << std::endl;

	Vector3 origin(-1, 0.5, 0);
	Vector3 direction(1, 0, 0);

	Ray r(origin, direction);

	std::cout << r << std::endl;

	IntersectionInfo info = t.getRayIntersection(r);

	std::cout << info << std::endl;

	origin = Vector3(2, -1, 0);
	direction = Vector3(2, 2, 0);

	r = Ray(origin, direction);

	std::cout << r << std::endl;

	info = t.getRayIntersection(r);

	std::cout << info << std::endl;

	origin = Vector3(0, 0, -1);
	direction = Vector3(0, 0, 1);

	r = Ray(origin, direction);

	std::cout << r << std::endl;

	info = t.getRayIntersection(r);

	std::cout << info << std::endl;
}