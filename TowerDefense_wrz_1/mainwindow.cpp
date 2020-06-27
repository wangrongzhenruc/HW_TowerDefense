#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button.h"
#include "tower0.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , towerType(0)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/mymusic/BGM.mp3"));
    player->setVolume(10);
    player->play();

    Button * startButton = new Button(QPixmap(":/myicons/startGame.png"));
    startButton->setParent(this);
    startButton->move(10, 640);
    connect(startButton, &Button::clicked, this, &MainWindow::gameStart);
    Button * quitButton = new Button(QPixmap(":/myicons/quitGame.png"));
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

    QPixmap tower1(":/myicons/tower1forplayer.png");
    QPixmap tower2(":/myicons/tower2forplayer.png");
    frontPainter->drawPixmap(5,150,150,150,tower1);
    frontPainter->drawPixmap(5,350,150,150,tower2);

    frontPainter->end();
    delete frontPainter;

    QPainter painter(this);
    painter.drawPixmap(pixmap.rect(), pixmap);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint pressPos = e->pos();
    if(_game.chooseTowerType(pressPos)==1){
        _game.setTower(pressPos, 1);
        towerType = 1;
    }
    else if(_game.chooseTowerType(pressPos)==2){
        _game.setTower(pressPos, 2);
        towerType = 2;
    }
    else if(towerType!=0){
        _game.setTower(pressPos, towerType);
    }
    else{}
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
}

