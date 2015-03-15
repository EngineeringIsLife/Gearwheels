#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T14:01:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gearwheel
TEMPLATE = app

#QMAKE_LFLAGS += /INCREMENTAL:NO

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/zahnrad.cpp \
    ../../src/zahnradmath.cpp \
    ../../src/gearwheeloutput.cpp \
    ../../src/zahnradprofil.cpp \
    ../../src/zahnradfertigung.cpp \
    qtoutputcontroller.cpp \
    mainlayout.cpp \
    qtoutputview.cpp

HEADERS  += mainwindow.h \
    ../../h/zahnrad.h \
    ../../h/zahnradmath.h \
    ../../h/gearwheeloutput.h \
    ../../h/zahnradprofil.h \
    ../../h/zahnradfertigung.h \
    qtoutputcontroller.h \
    mainlayout.h \
    qtoutputview.h \
    ../../h/setup.h

INCLUDEPATH += ../../h/

FORMS    +=
