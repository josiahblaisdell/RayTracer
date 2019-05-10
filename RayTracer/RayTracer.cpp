#include "RayTracer.h"

RayTracer::RayTracer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	CreateActions();
	omp_set_num_threads(4);
}

hitable_list RayTracer::TestScene()
{
	int n = 500;
	hitable_list world;
	world.list->push_back(new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5))));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			double choose_mat = uniformdistribution(eng);
			vec3 center(a + .9*uniformdistribution(eng), 0.2, b + 0.9*uniformdistribution(eng));
			if ((center - vec3(4,.2,0)).length() > .9)
			{
				if (choose_mat < .8) { //diffuse sphere
					world.list->push_back(new Sphere(center, 0.2, new Lambertian(vec3(uniformdistribution(eng)*uniformdistribution(eng), uniformdistribution(eng)*uniformdistribution(eng), uniformdistribution(eng)*uniformdistribution(eng)))));
				}
				else if (choose_mat < .95) { //metal sphere
					world.list->push_back(new Sphere(center, 0.2,
						new Metal(vec3(0.5*(1 + uniformdistribution(eng)), 0.5*(1 + uniformdistribution(eng)), 0.5*(1 + uniformdistribution(eng))), 0.5*(uniformdistribution(eng)))));
				}
				else { //glass
					world.list->push_back(new Sphere(center, 0.2, new Dielectric(1.5)));
				}
			}
		}
	}
	world.list->push_back(new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5)));
	world.list->push_back(new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4,0.2,0.1))));
	world.list->push_back(new Sphere(vec3(-4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5),0.0)));

	return world;
}

void RayTracer::CreateActions() {
	connect(ui.CreatePPM, &QAction::triggered, this, &RayTracer::on_actionCreatePPM_triggered);
}

vec3 RayTracer::color(const Ray & r, hitable_list world, int depth)
{
	HitRecord rec;
	//min is 0.0001 to resolve shadow acne problem
	if (world.hit(r, 0.001, DBL_MAX, rec)) {
		Ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_p->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
	}
	else {
		vec3 dir = unitize(r.direction());
		double t = .5*(dir.y() + 1.);
		return (1. - t)*vec3(1., 1., 1.) + t * vec3(.5, .7, 1.);
	}
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
		return (-b - sqrt(discr)) / (2. * a);
	}
	//if the discriminant>0 then the ray hits the sphere.

	//return (discr > 0);
}

void RayTracer::on_actionCreatePPM_triggered() {
	double lower_bound = 0;
	double upper_bound = 1;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	int nx = 1200;
	int ny = 800;
	int ns = 10;
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

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	double dist_to_focus = 10.0;
	double aperture = 0.1;

	Camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
	hitable_list world = TestScene();
	//world.list->push_back(new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(.294,0.,.51))));
	//world.list->push_back(new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(.8, .8, 0.))));
	//world.list->push_back(new Sphere(vec3(1, 0, -1), 0.5, new Metal(vec3(.8, .6, .2))));
	//glass has a ref_idx of 1.5 (1.3 - 1.7)
	//world.list->push_back(new Sphere(vec3(-1, 0, -1), 0.5, new Dielectric(1.5)));
	//world.list->push_back(new Sphere(vec3(-1, 0, -1), -0.45, new Dielectric(1.5)));
	//pixels are written in rows left to right
	//rows are written from top to bottom
	//red is 0 on left and goes to 1 on the right
	//green goes from 0 on the bottom to 1 at the top.
	of << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 c(0., 0., 0.);
	Ray ray;

	for (int j = ny - 1; j >= 0; j--)
	{

		for (int i = 0; i < nx; i++)
		{
			
			c = vec3(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				double u = double(i + unif(re)) / double(nx);
				double v = double(j + unif(re)) / double(ny);

				//when j = ny and i = 0 lower_left + u*horizontal + v*verticle = upper_right
				//First ray is shot at upper right corner going across then down.
				ray = cam.GetRay(u, v);
				vec3 p = ray[2.];
				c = c + color(ray, world,0);
			}

			c = c / double(ns);
			//sqrt is for gamma correction, in this case gamma = 2
			c = vec3(sqrt(c[0]), sqrt(c[1]), sqrt(c[2]));
			vec3 icolor(c[0] * 255.99, c[1] * 255.99, c[2] * 255.99);
			int ir = int(icolor[0]);
			int ig = int(icolor[1]);
			int ib = int(icolor[2]);
			of << ir << " " << ig << " " << ib << "\n";
		}
	}
	of.close();
}
