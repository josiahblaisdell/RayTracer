#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3
{
public:
	vec3() {}
	vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	//inline used because the execution time for these functions is less 
	//than the amount of time needed to load the instruction on the CPU.
	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }
	inline double r() const { return e[0]; }
	inline double g() const { return e[1]; }
	inline double b() const { return e[2]; }
	inline const vec3& operator+() const { return *this; }
	//negate the vector
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline double operator[](int i) const { return e[i]; }
	inline double& operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3 &v2);
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);

	inline vec3& operator*=(const double t);
	inline vec3& operator/=(const double t);
	inline vec3 operator+(const vec3 &v1, const vec3 &v2);

	inline vec3 unitize(vec3 v) { return v / v.length(); }

	inline double length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline double squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	double e[3];
	~vec3();
};

