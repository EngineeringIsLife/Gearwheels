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
    delete label_modul;
    delete slider_rotspeed;
    delete slider_rotsteps;
    delete label_status;
    delete output_toothcountspinner;
    delete output_toothcount2spinner;
    delete output_xspinner;
    delete output_modulcombo;
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
    char *ModulRow1[] = {"0.05", "0.06", "0.08", "0.10", "0.12", "0.16", "0.20", "0.25", "0.30", "0.40", "0.50", "0.60", "0.70", "0.80", \
                        "0.90", "1.00", "1.25", "1.5", "2.0", "2.5", "3", "4", "5", "6", "8", \
                        "10", "12", "16", "20", "25", "32", "40", "50", "60"};
    char *ModulRow2[] = {"0.055", "0.07", "0.09", "0.11", "0.14", "0.18", "0.22", "0.28", "0.35", "0.45", "0.55", "0.65", "0.75", "0.85", \
                        "0.95", "1.125", "1.375", "1.75", "2.25", "2.75", "3.5", "4.5", "5.5", "7", "9", \
                        "11", "14", "18", "22", "28", "36", "45", "55", "70"};

    // Third frame - Inputs for gearwheel
    box_output = new QGroupBox(parent);
    layout_main->addWidget(box_output, 3, 1, 1, 1);
    layout_output = new QVBoxLayout(box_output);

    QLabel* label_modul = new QLabel("Modul - Reihe 1");
    layout_output->addWidget(label_modul);
    output_modulcombo = new QComboBox(box_output);
    for (int i = 0; i < 31; i++) {
        QString str(ModulRow1[i]);
        output_modulcombo->addItem(str);
    }
    layout_output->addWidget(output_modulcombo);

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
