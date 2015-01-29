#include "mainwindow.h"
#include <QApplication>
#include <QPainter>

#include <iostream>
#include <fstream>

#include "bezugsprofil.h"
#include "zahnradmath.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 25);
    //ProfilMathematisch bezugMathe(zahnrad, 24);

    //ofstream myfile;
    //myfile.open("example.m");
    //bezugMathe.printProfileToMatlab(myfile);
    //myfile.close();

    return a.exec();
}

/*
void graphicsView::paintEvent(QPaintEvent *)
{

}*/
