#include "Camera.h"



Camera::Camera()
{
	origin = vec3(0., 0., 0.);
	lower_left_corner = vec3(-2., -1., -1.);
	horizontal = vec3(4., 0., 0.);
	vertical = vec3(0., 2., 0.);
	

}


Camera::~Camera()
{
}
