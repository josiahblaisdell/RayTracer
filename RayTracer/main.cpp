#include "RayTracer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RayTracer w;
	w.show();
	return a.exec();
}
