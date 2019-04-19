/********************************************************************************
** Form generated from reading UI file 'RayTracer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAYTRACER_H
#define UI_RAYTRACER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RayTracerClass
{
public:
    QAction *CreatePPM;
    QAction *LoadPPM;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RayTracerClass)
    {
        if (RayTracerClass->objectName().isEmpty())
            RayTracerClass->setObjectName(QStringLiteral("RayTracerClass"));
        RayTracerClass->resize(877, 669);
        CreatePPM = new QAction(RayTracerClass);
        CreatePPM->setObjectName(QStringLiteral("CreatePPM"));
        LoadPPM = new QAction(RayTracerClass);
        LoadPPM->setObjectName(QStringLiteral("LoadPPM"));
        centralWidget = new QWidget(RayTracerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        RayTracerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RayTracerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 877, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        RayTracerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RayTracerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RayTracerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RayTracerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RayTracerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(CreatePPM);
        menuFile->addAction(LoadPPM);

        retranslateUi(RayTracerClass);

        QMetaObject::connectSlotsByName(RayTracerClass);
    } // setupUi

    void retranslateUi(QMainWindow *RayTracerClass)
    {
        RayTracerClass->setWindowTitle(QApplication::translate("RayTracerClass", "RayTracer", nullptr));
        CreatePPM->setText(QApplication::translate("RayTracerClass", "Create PPM Image", nullptr));
        LoadPPM->setText(QApplication::translate("RayTracerClass", "Load PPM Image", nullptr));
        menuFile->setTitle(QApplication::translate("RayTracerClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RayTracerClass: public Ui_RayTracerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAYTRACER_H
