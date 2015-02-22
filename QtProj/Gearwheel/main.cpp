#include "mainwindow.h"
#include <QApplication>
#include <QWidget>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;

    w.show();
    return a.exec();
}
