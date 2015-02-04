#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpainter.h>
#include <iostream>

#include "bezugsprofil.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

using namespace std;

Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 5);
Zahnraddaten zahnrad2(20, .38, .25, 2.0, 0.0, 0.0, 25);
ProfilMathematisch zahn1(zahnrad, 100);
ProfilMathematisch zahn2(zahnrad2, 100);
GearwheelOutputQt output(zahn1.zahnprofil);
GearwheelOutputQt output2(zahn2.zahnprofil);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zahn2.moveGearwheel(zahnrad.durchmesser.d/2+zahnrad2.durchmesser.d/2,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
//    Bezugsprofil bezugsprofil(zahnrad, 2, 20);

    QPainter painter(this);
    painter.setPen(Qt::blue);


//    GearwheelOutputQt output2(bezugsprofil.profil);
    output.printToDisplay(painter, 200, 200, 5);
    output2.printToDisplay(painter, 200, 200, 5);
    zahn1.rotateGearwheel(10);
//    output2.printToDisplay(painter, 100,100, 30);
}

graphicsView::graphicsView(QWidget *parent)
{
    std::cout << "Graphics Konstruktor" << std::endl;
}
