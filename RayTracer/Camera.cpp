#include "Camera.h"



Camera::Camera()
{
	origin = vec3(0., 0., 0.);
	lower_left_corner = vec3(-2., -1., -1.);
	horizontal = vec3(4., 0., 0.);
	vertical = vec3(0., 2., 0.);
	

}

Camera::Camera(double vfov, double aspect)
{
	float theta = M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	lower_left_corner = vec3(-half_width, -half_height, -1.);
	horizontal = vec3(2 * half_width, 0.0, 0.0);
	vertical = vec3(0., 2 * half_height, 0.0);
	origin = vec3(0., 0., 0.);
}

Camera::Camera(vec3 pos, vec3 lookat, vec3 vup, double vfov, double aspect)
{
	float theta = vfov*M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = pos;
	w = unitize(pos - lookat);
	u = unitize(cross(vup, w));
	v = cross(w, u);
	lower_left_corner = vec3(-half_width, -half_height, -1.);
	lower_left_corner = origin - half_width * u - half_height * v - w;
	horizontal = 2 * half_width*u;
	vertical = 2 * half_height*v;
}

Camera::Camera(vec3 pos, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist)
{
	lens_radius = aperture / 2;

	double theta = vfov * M_PI / 180;
	double half_height = tan(theta / 2);
	double half_width = aspect * half_height;
	origin = pos;
	w = unitize(pos - lookat);
	u = unitize(cross(vup, w));
	v = cross(w, u);
	lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
	horizontal = 2 * half_width*focus_dist*u;
	vertical = 2 * half_height*focus_dist*v;
}


Camera::~Camera()
{
}
