#pragma once
#include "Ray.h"
class Camera
{
public:
	Camera();
	Ray GetRay(double u, double v){ return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }
	~Camera();

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

