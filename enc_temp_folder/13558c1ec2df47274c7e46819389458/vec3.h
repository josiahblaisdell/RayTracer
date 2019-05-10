#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>



//inline used because the execution time for these functions is less 
//than the amount of time needed to load the instruction on the CPU.
class vec3
{
public:
	//default constructor does nothing
	vec3() {}
	//constructor initializes array of 3 doubles
	vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	//getter for x coordinate
	inline double x() const { return e[0]; }
	//getter for y coordinate
	inline double y() const { return e[1]; }
	//getter for z coordinate
	inline double z() const { return e[2]; }
	//getter for r coordinate
	inline double r() const { return e[0]; }
	//getter for g coordinate
	inline double g() const { return e[1]; }
	//getter for b coordinate
	inline double b() const { return e[2]; }
	//Multiplying by 1 does nothing
	inline const vec3& operator+() const { return *this; }
	//Multiplying by -1 negates the vector
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	//Bracket accessor returns i'th element
	inline double operator[](int i) const { return e[i]; }
	//Bracket accessor returns a reference to the i'th element
	inline double& operator[](int i) { return e[i]; }
	//+= operator overload (ex v1 += v2;)
	inline vec3& operator+=(const vec3 &v2);
	//-= operator overload (ex v1 -= v2;)
	inline vec3& operator-=(const vec3 &v2);
	//*= operator overload (ex v1 *= v2;)
	inline vec3& operator*=(const vec3 &v2);
	// /= operator overload (ex v1 /= v2;)
	inline vec3& operator/=(const vec3 &v2);
	//*= operator overload (ex v1 *= 3.14;)
	inline vec3& operator*=(const double t);
	///= operator overload (ex v1 /= 3.14;)
	inline vec3& operator/=(const double t);
	//Returns the direction of the vector.
	inline vec3 direction() const { return vec3(e[0] / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]), e[1] / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]), e[2] / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2])) ; }
	//Returns the length of the vector.
	inline double length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	//Returns the length^2 of the original vector
	inline double squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	//Holds the data for the vector: x = e[0] , y = e[1], z = e[2]
	double e[3];
	~vec3();
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(double t, const vec3 &v1) {
	return vec3(t*v1.e[0], t*v1.e[1], t*v1.e[2]);
}

inline vec3 operator*(const vec3 &v1, double t) {
	return vec3(t*v1.e[0], t*v1.e[1], t*v1.e[2]);
}

inline vec3 operator/(const vec3 &v1, double t) {
	double div = 1 / t;
	return vec3(div*v1.e[0], div*v1.e[1], div*v1.e[2]);
}

inline vec3 operator/(double t, const vec3 &v1) {
	double div = 1 / t;
	return vec3(div*v1.e[0], div*v1.e[1], div*v1.e[2]);
}

inline double dot(const vec3 &v1, const vec3 &v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}
//Returns a unit vector pointing in the direction of the original vector.
inline vec3 unitize(vec3 v) { return v / v.length(); }
