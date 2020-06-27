#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include "position.h"
#include "tower1.h"
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

    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

protected slots:
    void updateMap();
    void gameStart();
    void receivelogin();//与login中发射的信号关联的槽函数


private:
    Ui::MainWindow *ui;
    World _game;
    QTimer *timer;
    int towerType;
};
#endif // MAINWINDOW_H
