#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter *frontPainter;
    frontPainter = new QPainter();
    QPixmap pixmap("/Users/shaner/Qt_files/TowerDefense_wrz_1/icons_2/map1.png");
    frontPainter->begin(&pixmap);

    int n1 = _game._towerVector.size();
    for (int i=0;i<n1;i++){
        _game._towerVector[i]->show(frontPainter);
    }

    int n2 = EnemyRoad::ROADPOINT_VECTOR.size();
    /*for (int i=0;i<n2;i++){
        EnemyRoad::ROADPOINT_VECTOR[i]->show(frontPainter);
    }*/

    frontPainter->end();
    delete frontPainter;

    QPainter painter(this);
    painter.drawPixmap(pixmap.rect(), pixmap);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint pressPos = e->pos();
    _game.setTower(pressPos);
    this->update();
}


