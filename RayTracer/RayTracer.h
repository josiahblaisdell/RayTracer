#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RayTracer.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>
#include <random>
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Camera.h"
static std::normal_distribution<double> dist(0.0, 1.0);
static std::default_random_engine eng;
static vec3 random_in_unit_sphere() {
	vec3 p(0,0,0);

	while (p.squared_length() < .0001) {
		double x = dist(eng);
		double y = dist(eng);
		double z = dist(eng);
		p = vec3(x, y, z);
	}
	p = p / p.squared_length();
	return p;
}

class RayTracer : public QMainWindow
{
	Q_OBJECT

public:
	RayTracer(QWidget *parent = Q_NULLPTR);

private:
	Ui::RayTracerClass ui;
	void CreateActions();
	vec3 color(const Ray& r, hitable_list world);

	float hitsphere(const vec3& center, float radius, const Ray& r);

private slots:
	void on_actionCreatePPM_triggered();
};
