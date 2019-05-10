#pragma once
#include "vec3.h"
#include "Ray.h"
#include <random>
#include <vector>

class Material;

static std::normal_distribution<double> normaldistribution(0.0, 1.0);
static std::uniform_real_distribution<double> uniformdistribution(0.0, 1.0);
static std::default_random_engine eng;
static vec3 random_in_unit_sphere() {
	vec3 p(0, 0, 0);

	while (p.squared_length() < .0001) {
		double x = normaldistribution(eng);
		double y = normaldistribution(eng);
		double z = normaldistribution(eng);
		p = vec3(x, y, z);
	}
	p = p / p.squared_length();
	return p;
}

static vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n)*n;
}

static bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = unitize(v);
	float dt = dot(uv, n);
	float disc = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	//if disc <= 0 then the ray is in the material with the higher refractive index, 
	//		no refraction is possible, all light is reflected
	if (disc > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(disc);
		return true;
	}
	else {
		return false;
	}
}

//polynomial expension to compute reflectivity w/r/t angle 
static float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow(1 - cosine, 5);
}

struct HitRecord
{
	//time variable for things like motion blur
	double t;
	//point that was hit
	vec3 p;
	//normal vector at the point that was his
	vec3 normal;

	//hitables and materials need to know about eachother
	//materials will define how rays interract with surface
	//When a ray hits a surface (a particular sphere for example), the material pointer in the
	//	hit_record will be set to point at the material pointer the sphere was given when it was set up in
	//	main() when we start.When the color() routine gets the hit_record it can call member
	//	functions of the material pointer to find out what ray, if any, is scattered.
	Material* mat_p;
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
	Sphere(vec3 cen, double r, Material* m);
	virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
	vec3 center;
	double radius;
	Material* mat;
};