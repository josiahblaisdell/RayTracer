#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RayTracer.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>
#include "vec3.h"
#include "Ray.h"

class RayTracer : public QMainWindow
{
	Q_OBJECT

public:
	RayTracer(QWidget *parent = Q_NULLPTR);

private:
	Ui::RayTracerClass ui;
	void CreateActions();
	vec3 color(const Ray& r);

	float hitsphere(const vec3& center, float radius, const Ray& r);

private slots:
	void on_actionCreatePPM_triggered();
};
