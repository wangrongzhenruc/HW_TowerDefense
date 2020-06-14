#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include "position.h"
#include "tower0.h"
#include "enemyroad.h"
#include "world.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

protected slots:
    void updateMap();
    void gameStart();


private:
    Ui::MainWindow *ui;
    World _game;
    QTimer *timer;
};
#endif // MAINWINDOW_H
