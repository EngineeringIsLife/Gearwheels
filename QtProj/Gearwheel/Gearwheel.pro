#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T14:01:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gearwheel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/zahnrad.cpp \
    ../../src/zahnradmath.cpp \
    ../../src/gearwheeloutput.cpp \
    ../../src/zahnradprofil.cpp \
    ../../src/zahnradfertigung.cpp

HEADERS  += mainwindow.h \
    ../../h/zahnrad.h \
    ../../h/zahnradmath.h \
    ../../h/gearwheeloutput.h \
    ../../h/zahnradprofil.h \
    ../../h/zahnradfertigung.h

INCLUDEPATH += /home/daniel/Documents/dev/Gearwheel/h/

FORMS    +=
