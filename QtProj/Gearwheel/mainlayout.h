#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <iostream>

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>

#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

#include "qtoutputview.h"

class MainLayout : public QObject
{
    Q_OBJECT

private:
    QWidget* parent;
    // Layout-Items
    QGridLayout* layout_main;
    QGroupBox* box_buttons;
    QGroupBox* box_output;
    QLabel* label_title;
    QHBoxLayout* layout_buttons;
    QVBoxLayout* layout_output;
    QLabel* label_testtext;
    QLabel* label_status;

    void createToplevelLayout(QWidget *parent = 0);
    void createTitleFrame(void);
    void createButtonsFrame(void);
    void createOutputFrame(void);
    void createStatusFrame(void);

public:
    QPushButton* rotateButton;
    QPushButton* secondGWButton;
    QPushButton* centerGWButton;
    QPushButton* exitButton;
    QSlider* slider_rotspeed;
    QSlider* slider_rotsteps;
    QSpinBox* output_toothcountspinner;
    QSpinBox* output_toothcount2spinner;
    QDoubleSpinBox* output_xspinner;
    QCheckBox* output_diametercheckbox;
    QCheckBox* output_footdiametercheckbox;
    QCheckBox* output_outerdiametercheckbox;
    QCheckBox* output_basediametercheckbox;

    MainLayout(QWidget *parent = 0);
    ~MainLayout(void);
    void addView(QGraphicsView *view);
    void changeStatusText(QString newText);
    void changeRotButtonText(QString newText);
    void changeSecGWButtonText(QString newText);

public slots:
    void gearwheelRotationState(bool state);
    void secondGWVisibility(bool state);
};

#endif // MAINLAYOUT_H
