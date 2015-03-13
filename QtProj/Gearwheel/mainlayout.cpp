#include "mainlayout.h"

MainLayout::MainLayout(QWidget *parent)
    : parent(parent)
{
    createToplevelLayout(parent);
}

MainLayout::~MainLayout(void)
{
    delete layout_main;
    delete box_buttons;
    delete box_output;
    delete label_title;
    delete layout_buttons;
    delete rotateButton;
    delete secondGWButton;
    delete exitButton;
    delete layout_output;
    delete label_testtext;
    delete slider_rotspeed;
    delete slider_rotsteps;
    delete label_status;
    delete output_toothcountspinner;
    delete output_toothcount2spinner;
    delete output_xspinner;
}

void MainLayout::addView(QGraphicsView *view)
{
    layout_main->addWidget(view, 3,2,1,1);
}

void MainLayout::changeStatusText(QString newText)
{
    label_status->setText(newText);
}

void MainLayout::changeRotButtonText(QString newText)
{
    rotateButton->setText(newText);
}

void MainLayout::changeSecGWButtonText(QString newText)
{
    secondGWButton->setText(newText);
}

void MainLayout::gearwheelRotationState(bool state)
{
    if (state) {
        rotateButton->setText("Rotation stoppen");
        label_status->setText("Rotation gestartet");
    }
    else {
        rotateButton->setText("Rotation starten");
        label_status->setText("Rotation angehalten");
    }
}

void MainLayout::secondGWVisibility(bool state)
{
    if (state) {
        secondGWButton->setText("Zweites Zahnrad ausblenden");
    }
    else {
        secondGWButton->setText("Zweites Zahnrad einblenden");
    }
}
