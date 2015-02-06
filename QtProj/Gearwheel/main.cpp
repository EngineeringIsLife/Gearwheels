#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>

#include <iostream>
#include <fstream>

#include "zahnradfertigung.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;

    //Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 5);
    //ProfilMathematisch prof(zahnrad, 100);
    //ZahnradFertigung bezugsprofil(zahnrad, 2, (int)20);

    //Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 25);
    //ProfilMathematisch bezugMathe(zahnrad, 24);

    //ofstream myfile;
    //myfile.open("example.m");
    //bezugMathe.printProfileToMatlab(myfile);
    //myfile.close();

    //GearwheelOutput output(bezugsprofil.zahnprofil);
    //GearwheelOutput output2(prof.zahnprofil);
    //output.printProfile(std::cout);
    //output.printProfileToMatlab(std::cout);

    //QPushButton *button = new QPushButton("&Exit");
    //QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));

    //QObject::connect()
    //QVBoxLayout *layout = new QVBoxLayout(&w);
    //layout->addWidget(button);

    w.show();
    return a.exec();
}
