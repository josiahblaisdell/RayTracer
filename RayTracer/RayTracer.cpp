#include "RayTracer.h"

RayTracer::RayTracer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	CreateActions();
}

void RayTracer::CreateActions() {
	connect(ui.CreatePPM, &QAction::triggered, this, &RayTracer::on_actionCreatePPM_triggered);
}

vec3 RayTracer::color(const Ray & r)
{
	//if this ray hits the sphere color the pixel red.
	if (hitsphere(vec3(0, 0, -1), 0.5, r)) { return vec3(1, 0, 0); }
	vec3 dir = unitize(r.direction());
	//0 <= t <= 1
	double t = .5*(dir.y() + 1.);
	if(t>0)
	//blended value = (1-t)*start + t*end
	return (1 - t)*vec3(1., 1., 1.) + t * vec3(.5, .7, 1.);
}

float RayTracer::hitsphere(const vec3 & center, float radius, const Ray & r)
{
	//origin to center of sphere
	vec3 o_c = r.origin() - center;
	//equation for circle ( p-c,p-c ) = (p,p) - 2(p,c) + (c,c)
	//								  = (A + Bt,A+Bt) - 2(A+Bt,c) + (c,c)
	//let c = r-c					  = (A,A) + 2(A,Bt) + (Bt,Bt) - 2(A,c) - 2(Bt,c) + (c,c)
	//								  = (A,A) + 2t(B,A) + t^2(B,B) - 2(A,c) -2t(B,c) + (c,c)
	//								  = (A,A) + 2t(B,A-c) + t^2(B,B) + (c,c)
	//	 							  = (A,A) + 2t(B,A-c) + t^2(B,B) + (-c,-c)
	//	 							  = (A-c,A-c) + 2t(B,A-c) + t^2(B,B)
	//								  = R*R
	// o_c = c
	// r.direction() = B
	// r.origin() = A
	// in the quadratic formulat ax^2 + bx + c = 0 -> roots of {[-b + sqrt(b^2 - 4ac)]/2a,[-b + sqrt(b^2 - 4ac)]/2a}
	// I will now find a,b and c using equation for circle above.
	double a = dot(r.direction(), r.direction());
	double b = 2.0*dot(r.direction(), o_c);
	double c = dot(o_c, o_c) - radius * radius;
	double discr = b * b - 4 * a*c;
	if (discr < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discr)) / (2 * a);
	}
	//if the discriminant>0 then the ray hits the sphere.

	return (discr > 0);
}

void RayTracer::on_actionCreatePPM_triggered() {
	int nx = 480;
	int ny = 270;
	std::string filepath = "image.ppm";
	std::ofstream of;
	of.open(filepath.c_str(), std::ios_base::app);

	//lower left corner of image
	vec3 lower_left(-2., -1., -1.);
	//lower_left + horizontal = lower_right
	vec3 horizontal(4., 0., 0.);
	//lower_left + verticle = upper right
	vec3 verticle(0., 2., 0.);
	//location of the camera
	vec3 origin(0., 0., 0.);

	//pixels are written in rows left to right
	//rows are written from top to bottom
	//red is 0 on left and goes to 1 on the right
	//green goes from 0 on the bottom to 1 at the top.
	of << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny -1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			double u = double(i) / double(nx);
			double v = double(j) / double(ny);
			//when j = ny and i = 0 lower_left + u*horizontal + v*verticle = upper_right
			//First ray is shot at upper right corner going across then down.
			Ray ray(origin,lower_left + u*horizontal + v*verticle);
			vec3 c = color(ray);
			vec3 icolor(c[0] * 255.99, c[1] * 255.99, c[2] * 255.99);
			int ir = int(icolor[0]);
			int ig = int(icolor[1]);
			int ib = int(icolor[2]);
			of << ir << " " << ig << " " << ib << "\n";
		}
	}
	of.close();
}
