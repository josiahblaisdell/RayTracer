#pragma once
#include "vec3.h"
#include "Ray.h"
#include <vector>
struct HitRecord
{
	//time variable for things like motion blur
	double t;
	//point that was hit
	vec3 p;
	//normal vector at the point that was his
	vec3 normal;
};

class hitable {
public:
	//hit only counts if it is between tmin and tmax
	virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const = 0;
};

class hitable_list : public hitable {
public:
	hitable_list() { list = new std::vector<hitable*>(); }
	virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
	std::vector<hitable*> *list;
};

class Sphere : public hitable {
public:
	Sphere() {}
	Sphere(vec3 cen, double r);
	virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
	vec3 center;
	double radius;
};