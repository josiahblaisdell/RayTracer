#pragma once
#include "Ray.h"
#include "Hitable.h"
#include <math.h>
#define M_PI 3.14159265358979323846264338327950288
class Camera
{
public:
	Camera();
	Camera(double vfov, double aspect);
	Camera(vec3 pos, vec3 lookat, vec3 vup, double vfov, double aspect);
	Camera(vec3 pos, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist);

	Ray GetRay(double s, double t){ 
		vec3 rd = lens_radius * random_in_unit_sphere();
		vec3 offset = u * rd.x() + v * rd.y();
		return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}
	~Camera();

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};

