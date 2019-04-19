#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RayTracer.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>

class RayTracer : public QMainWindow
{
	Q_OBJECT

public:
	RayTracer(QWidget *parent = Q_NULLPTR);

private:
	Ui::RayTracerClass ui;
	void CreateActions();
private slots:
	void on_actionCreatePPM_triggered();
};
