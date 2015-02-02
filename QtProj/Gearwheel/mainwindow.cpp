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
    Bezugsprofil bezugsprofil(zahnrad, 2, 20);

    QPainter painter(this);
    painter.setPen(Qt::blue);

    GearwheelOutputQt output(prof.zahnprofil);
    //GearwheelOutputQt output(bezugsprofil.profil_neu);
    output.printToDisplay(painter, 200, 200, 10);


}

graphicsView::graphicsView(QWidget *parent)
{
    std::cout << "Graphics Konstruktor" << std::endl;
}
