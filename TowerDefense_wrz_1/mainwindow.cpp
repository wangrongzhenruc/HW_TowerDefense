#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    QTimer::singleShot(30, this, SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    if (World::isWin || World::isLose)
    {
        QString text = World::isLose ? "YOU LOSE!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPainter *frontPainter;
    frontPainter = new QPainter();
    QPixmap pixmap;
    pixmap.load(":/myicons/map1.png");
    frontPainter->begin(&pixmap);

    int n1 = World::TOWER_VECTOR.size();
    for (int i=0;i<n1;i++){
        World::TOWER_VECTOR[i]->show(frontPainter);
    }

    int n2 = World::ENEMY_VECTOR.size();
    for (int i=0;i<n2;i++){
        World::ENEMY_VECTOR[i]->show(frontPainter);
    }

    int n3 = World::BULLET_VECTOR.size();
    for (int i=0;i<n3;i++){
        World::BULLET_VECTOR[i]->show(frontPainter);
    }


    /*int n2 = EnemyRoad::ROADPOINT_VECTOR.size();
    for (int i=0;i<n2;i++){
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

void MainWindow::updateMap(){
    int n1 = World::ENEMY_VECTOR.size();
    for (int i=0;i<n1;i++){
        _game.enenyMove(* World::ENEMY_VECTOR[i]);
    }
    int n2 = World::TOWER_VECTOR.size();
    for (int i=0;i<n2;i++){
        World::TOWER_VECTOR[i]->checkEnemyInRange();
    }

    this->update();
}

void MainWindow::gameStart()
{
    this->_game.loadWave();
}

