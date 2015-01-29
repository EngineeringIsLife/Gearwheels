#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class graphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit graphicsView(QWidget *parent);
};

#endif // MAINWINDOW_H
