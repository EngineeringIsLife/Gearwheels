#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpainter.h>
#include <iostream>

#include "bezugsprofil.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 5);
    ProfilMathematisch prof(zahnrad, 100);

    QPainter painter(this);
    painter.setPen(Qt::blue);

    const int startx = 200;
    const int starty = 200;

    float scale = 10;

    prof.resetIterator();
    int p1=startx, p2=starty;

    for (int i = 0; i < prof.zahnprofil.elemente; i++)
    {
        int p3 = (int)(prof.getNextX() * scale) + startx;
        int p4 = (int)(prof.getNextY() * scale) + starty;
        painter.drawLine(p1,p2,p3,p4);
        p1 = p3;
        p2 = p4;
    }

    GearwheelOutput output(prof.zahnprofil);
    //output.printProfile(std::cout);
}

graphicsView::graphicsView(QWidget *parent)
{
    std::cout << "Graphics Konstruktor" << std::endl;
}
