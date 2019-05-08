#pragma once
#include "Ray.h"
#include "Hitable.h"
class Material
{
public:
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
};

