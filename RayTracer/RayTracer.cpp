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

void RayTracer::on_actionCreatePPM_triggered() {
	int nx = 200;
	int ny = 100;
	std::string filepath = "image.ppm";
	std::ofstream of;
	of.open(filepath.c_str(), std::ios_base::app);

	//pixels are written in rows left to right
	//rows are written from top to bottom
	//red is 0 on left and goes to 1 on the right
	//green goes from 0 on the bottom to 1 at the top.
	of << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny -1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			of << ir << " " << ig << " " << ib << "\n";
		}
	}
	of.close();
}
