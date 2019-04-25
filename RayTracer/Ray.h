#pragma once
#include "vec3.h"

class Ray
{
public:
	Ray();
	//Constructor: two vec3 specify a line in 3D.
	Ray(const vec3& a, const vec3& b) { A = a; B = b; }
	//Get the intercept
	vec3 origin() const { return A; }
	//Get the direction of the ray (not unitized)
	vec3 direction() const { return B; }
	//Evaluate the function that defines the line at t
	vec3 operator[](double t) const { return A + t*B; }
	//The intercept of the line (the value when t = 0)
	vec3 A;
	//The direction of the line.
	vec3 B;
	//default destructor
	~Ray();
};