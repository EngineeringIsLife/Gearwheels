#include "mainwindow.h"
#include <QApplication>
#include <QPainter>

#include <iostream>
#include <fstream>

#include "bezugsprofil.h"
#include "zahnradmath.h"
#include "gearwheeloutput.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 5);
    ProfilMathematisch prof(zahnrad, 100);
    Bezugsprofil bezugsprofil(zahnrad, 2, 20);

    //Zahnraddaten zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 25);
    //ProfilMathematisch bezugMathe(zahnrad, 24);

    //ofstream myfile;
    //myfile.open("example.m");
    //bezugMathe.printProfileToMatlab(myfile);
    //myfile.close();

    GearwheelOutput output(bezugsprofil.profil);
    GearwheelOutput output2(prof.zahnprofil);
    //output.printProfileToMatlab(std::cout);

    return a.exec();
}
