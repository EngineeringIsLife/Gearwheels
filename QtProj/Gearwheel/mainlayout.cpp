#include "mainlayout.h"
#include "setup.h"

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
    delete centerGWButton;
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

void MainLayout::createToplevelLayout(QWidget *parent)
{
    layout_main = new QGridLayout(parent);

    createTitleFrame();
    createButtonsFrame();
    createOutputFrame();
    createStatusFrame();

    gearwheelRotationState(false);
    secondGWVisibility(false);
}

void MainLayout::createTitleFrame(void)
{
    // First frame - Title
    label_title = new QLabel();
    layout_main->addWidget(label_title, 1, 1, 1, 2);
    label_title->setText("Softwaretool zur Generierung evolventischer Zahnformen");
}

void MainLayout::createButtonsFrame(void)
{
    // Second frame - Buttons
    box_buttons = new QGroupBox(parent);
    layout_main->addWidget(box_buttons, 2, 1, 1, 2);
    layout_buttons = new QHBoxLayout(box_buttons);

    rotateButton = new QPushButton(box_buttons);
    secondGWButton = new QPushButton(box_buttons);
    centerGWButton = new QPushButton("Zentriere Zahnrad", box_buttons);
    exitButton = new QPushButton("Beenden", box_buttons);

    layout_buttons->addWidget(rotateButton);
    layout_buttons->addWidget(secondGWButton);
    layout_buttons->addWidget(centerGWButton);
    layout_buttons->addWidget(exitButton);
}

void MainLayout::createOutputFrame(void)
{
    // Third frame - Inputs for gearwheel
    box_output = new QGroupBox(parent);
    layout_main->addWidget(box_output, 3, 1, 1, 1);
    layout_output = new QVBoxLayout(box_output);

    //label_testtext = new QLabel(box_output);
    //label_testtext->setText("Einstellungen");
    //layout_output->addWidget(label_testtext);

    QLabel* label_toothcount1 = new QLabel("Zahnrad 1 - Zähnezahl");
    layout_output->addWidget(label_toothcount1);
    output_toothcountspinner = new QSpinBox(box_output);
    output_toothcountspinner->setRange(GW_Z_MIN,GW_Z_MAX);
    layout_output->addWidget(output_toothcountspinner);

    QLabel* label_toothcount2 = new QLabel("Zahnrad 2 - Zähnezahl");
    layout_output->addWidget(label_toothcount2);
    output_toothcount2spinner = new QSpinBox(box_output);
    output_toothcount2spinner->setRange(GW_Z_MIN,GW_Z_MAX);
    layout_output->addWidget(output_toothcount2spinner);

    output_diametercheckbox = new QCheckBox("Zeige Durchmesser", box_output);
    layout_output->addWidget(output_diametercheckbox);
    output_footdiametercheckbox = new QCheckBox("Zeige Fußkreisdurchmesser", box_output);
    layout_output->addWidget(output_footdiametercheckbox);
    output_outerdiametercheckbox = new QCheckBox("Zeige Außendurchmesser", box_output);
    layout_output->addWidget(output_outerdiametercheckbox);
    output_basediametercheckbox = new QCheckBox("Zeige Basiskreis", box_output);
    layout_output->addWidget(output_basediametercheckbox);

    QLabel* label_xmovement = new QLabel("Profilverschiebung");
    layout_output->addWidget(label_xmovement);
    output_xspinner = new QDoubleSpinBox(box_output);
    output_xspinner->setRange(GW_X_MIN, GW_X_MAX);
    output_xspinner->setSingleStep(0.1);
    layout_output->addWidget(output_xspinner);

    QLabel* label_rotspeed = new QLabel("Rotationsgeschwindigkeit");
    layout_output->addWidget(label_rotspeed);
    slider_rotspeed = new QSlider(Qt::Horizontal, box_output);
    layout_output->addWidget(slider_rotspeed);

    QLabel* label_rotdetail = new QLabel("Rechenschrittweite");
    layout_output->addWidget(label_rotdetail);
    slider_rotsteps = new QSlider(Qt::Horizontal, box_output);
    layout_output->addWidget(slider_rotsteps);
}

void MainLayout::createStatusFrame(void)
{
    // Fourth frame - Status bar
    label_status = new QLabel();
    label_status->setText("Bereit");

    layout_main->addWidget(label_status, 4, 1, 1, 2);
}
