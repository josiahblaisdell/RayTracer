#pragma once
#include "Ray.h"
#include "Hitable.h"
//material will tell us how rays interact with the surface
class Material
{
public:
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const vec3& a) { albedo = a; }
	//scatter the ray in a random direction
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
	vec3 albedo;
};

class Metal : public Material
{
public:
	Metal(vec3& a, double f) { albedo = a; fuzz = f; }
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
	vec3 albedo;
	//radius of sphere used to randomize the reflected direction (to give brushed metal effect)
	//fuzz = 0 is perfectly polished, fuzz of .3 - 1.0 looks like brushed metal
	double fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(float ri) { ref_idx = ri; }
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
	double ref_idx;
};