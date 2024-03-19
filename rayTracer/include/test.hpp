#pragma once

#include "ray.hpp";

void testVector() {

	Vector3 v1(0, 3, 0);
	Vector3 v2(5, 5, 0);

	std::cout << "Sum of " << v1 << " and " << v2 << ": " << v1 + v2 << std::endl;
	std::cout << "Subtraction of " << v1 << " from " << v2 << ": " << v2 - v1 << std::endl;
	std::cout << "Multiplication of " << v1 << " by 2: " << v1 * 2 << std::endl;
	std::cout << "Division of " << v1 << " by 2: " << v1 / 2 << std::endl;
	std::cout << "Angle between " << v1 << " and " << v2 << ": " << v1.angle(v2) << std::endl;
	std::cout << "Cross product of " << v1 << " and " << v2 << ": " << v1.cross(v2) << std::endl;
	std::cout << "Dot product of " << v1 << " and " << v2 << ": " << v1 * v2 << std::endl;
	std::cout << "Normalized vector " << v2 << ": " << v2.normalize() << std::endl;

}
 
void testRay() {

	Vector3 p1(1, 2, 3);
	Vector3 p2(4, 5, 6);
	Vector3 p3(15, 19.5, 24);
	Vector3 p4(-3, -3, -3);

	Ray ray(p1, p2);

	std::cout << "Ray -> " << ray << std::endl;

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
	// TODO
}

void testPlane() {
	// TODO
}