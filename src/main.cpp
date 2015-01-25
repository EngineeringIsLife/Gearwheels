#include <QCoreApplication>
#include <iostream>
#include <fstream>

#include "bezugsprofil.h"

/* Bezugsprofil:
 * int elemente
 * float *profil
 * float *profx
 */

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Zahnrad zahnrad(20, .38, .25, 2.0, 0.0, 0.0, 25);

    Bezugsprofil bezug(zahnrad, 2.0, 100);
    //cout << "Bezugsprofil klassisch fertig" << endl;
    ProfilMathematisch bezugMathe(zahnrad, 24);
    //cout << "Matheprofil fertig" << endl;

    bezug.calcBezugsprofil();

    //cout << "Profile berechnet" << endl;

    bezugMathe.printProfile(cout);

    //cout << "Profile ausgegeben" << endl;

    ofstream myfile;
    myfile.open ("example.m");
    //cout << "Datei geoeffnet" << endl;
    //bezug.printProfileToMatlab(myfile);
    bezugMathe.printProfileToMatlab(myfile);
    //cout << "In Datei geschrieben" << endl;
    myfile.close();
    //cout << "Datei geschlossen" << endl;

    cout << "Done" << endl;

    return a.exec();
}
