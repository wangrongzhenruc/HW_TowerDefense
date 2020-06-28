#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tower0.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , towerType(0)
{
    ui->setupUi(this);
    this->setFixedSize(960, 767);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/mymusic/BGM.mp3"));
    player->setVolume(10);
    player->play();

    startButton = new Button(QPixmap(":/myicons/startGame.png"));
    startButton->setParent(this);
    startButton->move(10, 640);
    connect(startButton, &Button::clicked, this, &MainWindow::gameStart);
    quitButton = new Button(QPixmap(":/myicons/quitGame.png"));
    quitButton->setParent(this);
    quitButton->move(10, 690);
    connect(quitButton, &Button::clicked, this, &QApplication::quit);
}


void MainWindow::receivelogin()
{
    this->show();//显示主窗口
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    if (World::isWin || World::isLose)
    {
        QPainter painter(this);
        if(World::isLose){
            QPixmap pixmap(":/myicons/lose.jpg");
            painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
        }
        else{
            QPixmap pixmap(":/myicons/win.jpg");
            painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
        }
        return;
    }

    QPainter *frontPainter;
    frontPainter = new QPainter();
    QPixmap pixmap;
    pixmap.load(":/myicons/map1.png");
    frontPainter->begin(&pixmap);

    int n1 = World::TOWER_0_VECTOR.size();
    for (int i=0;i<n1;i++){
        World::TOWER_0_VECTOR[i]->show(frontPainter);
    }

    int n2 = World::ENEMY_VECTOR.size();
    for (int i=0;i<n2;i++){
        World::ENEMY_VECTOR[i]->show(frontPainter);
    }

    int n3 = World::BULLET_VECTOR.size();
    for (int i=0;i<n3;i++){
        World::BULLET_VECTOR[i]->show(frontPainter);
    }

    int n4 = World::TOWER_2_VECTOR.size();
    for (int i=0;i<n4;i++){
        World::TOWER_2_VECTOR[i]->show(frontPainter);
    }

    QFont font("宋体", 30, QFont::Bold);
    frontPainter->setFont(font);
    frontPainter->setPen(Qt::red);
    frontPainter->drawText(700, 50, QString("敌人波数 : %1").arg(_game.Waves + 1));
    frontPainter->drawText(150, 50, QString("基地血条 : %1").arg(_game.BaseHP));
    frontPainter->drawText(450, 50, QString("财力 : %1").arg(_game.PlayerGold));

    frontPainter->drawPixmap(5,150,150,150,QPixmap(":/myicons/tower1forplayer.png"));
    frontPainter->drawPixmap(5,350,150,150,QPixmap(":/myicons/tower2forplayer.png"));
    frontPainter->drawPixmap(10,550,80,80,QPixmap(":/myicons/eraser.png"));
    frontPainter->drawPixmap(300,640,80,80,QPixmap(":/myicons/enemy_green1forplayer.png"));
    frontPainter->drawPixmap(450,640,80,80,QPixmap(":/myicons/enemyHPforplayer.png"));
    frontPainter->drawPixmap(600,640,80,80,QPixmap(":/myicons/enemyFlashforplayer.png"));
    frontPainter->end();
    delete frontPainter;

    QPainter painter(this);
    painter.drawPixmap(pixmap.rect(), pixmap);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint pressPos = e->pos();
    if(_game.chooseTowerType(pressPos)==1){
        towerType = 1;
    }
    else if(_game.chooseTowerType(pressPos)==2){
        towerType = 2;
    }
    else if(_game.chooseTowerType(pressPos)==3){
        towerType += 100;
    }
    else if(towerType==1||towerType==2){
        _game.setTower(pressPos, towerType);
    }
    else if(towerType==102||towerType==101){
        _game.eraseTower(pressPos);
    }
    else{}
    this->update();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e){
    QPoint pressPos = e->pos();
    _game.updateTower(pressPos);
    this->update();
}

void MainWindow::updateMap(){
    int n1 = World::ENEMY_VECTOR.size();
    for (int i=0;i<n1;i++){
        _game.enenyMove(* World::ENEMY_VECTOR[i]);
    }
    int n2 = World::TOWER_0_VECTOR.size();
    for (int i=0;i<n2;i++){
        World::TOWER_0_VECTOR[i]->checkEnemyInRange();
    }
    int n3 = World::TOWER_2_VECTOR.size();
    for (int i=0;i<n3;i++){
        World::TOWER_2_VECTOR[i]->checkEnemyInRange();
    }

    this->update();
}

void MainWindow::gameStart()
{
    this->_game.loadWave();
    delete(startButton);
    startButton = NULL;
}

