#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
//#include <QPainter>
//#include <QMainWindow>

//class MainWindow : public QMainWindow
class MainWidget : public QWidget
{
    Q_OBJECT

private:
    //Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;

    bool rotationStarted;
    float zoom;
    float angle;

    void updateGearwheel(void);

    //virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);  // Replace with wheelEvent

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void rotationTimer(void);
    void toggleRotation(void);
};

#endif // MAINWINDOW_H
