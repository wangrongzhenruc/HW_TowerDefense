#include "enemy.h"
#include "mainwindow.h"
//#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>


const int Enemy::MAX_HP=450;
const int Enemy::HP_LEN=70;
const int Enemy::ENEMY_SIZE=70;
const int Enemy::SPEED=2;

Enemy::Enemy(EnemyRoad *startWayPoint, int type)
    : QObject(0)
    , _active(false)
    , _isBlock(false)
    , _type(type)
    , _currentHP(MAX_HP)
    , _speed(SPEED)
    , _rotationSprite(0.0)
    , _position(startWayPoint->getPosition())
    , _nextStep(startWayPoint->getNextPoint())
{
    if(type==0){
        _pixmap.load(":/myicons/enemy_green1.png");
    }
    else if(type==1){
        _pixmap.load(":/myicons/enemyHP.png");
        _currentHP = 1.5*MAX_HP;
    }
    else{
        _pixmap.load(":/myicons/enemyFlash.png");
        _speed = 1.5*SPEED;
    }
}

Enemy::~Enemy()
{
    _attackerTowers0.clear();
    _attackerTowers2.clear();
    _nextStep = NULL;
    //m_game = NULL;
}

void Enemy::setShowBlock(bool isShow) {
    if(isShow) {
        _isBlock = true;
    }
    else{
        _isBlock = false;
    }
}

void Enemy::show(QPainter *painter) const{
    if (!_active)
        return;

    painter->save();
    QPoint deltaP(ENEMY_SIZE/2, ENEMY_SIZE/2);//中心点与_position的偏移
    painter->translate(this->_position-deltaP);//以左上角点作为坐标原点

    if(_isBlock){
        QPixmap block(":/myicons/bullet2.png");
        painter->drawPixmap(0,0,Enemy::ENEMY_SIZE, Enemy::ENEMY_SIZE, block);
    }

    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);
    QRect HPBackRect(QPoint(0,-ENEMY_SIZE/4), QSize(HP_LEN, 5));
    painter->drawRect(HPBackRect);

    painter->setBrush(Qt::green);
    double length;
    if(_type == 1){
        length = (double(_currentHP)/double(1.5*MAX_HP))*double(HP_LEN);
    }
    else{
        length = (double(_currentHP)/double(MAX_HP))*double(HP_LEN);
    }
    QRect HPFrontRect(QPoint(0,-ENEMY_SIZE/4), QSize(length, 5));
    painter->drawRect(HPFrontRect);

    painter->drawPixmap(0,0,Enemy::ENEMY_SIZE, Enemy::ENEMY_SIZE, _pixmap);
    painter->restore();
}

void Enemy::goOnNextPosition(){
    this->_position = this->_nextStep->getPosition();
    this->_nextStep = this->_nextStep->getNextPoint();
}

void Enemy::move(){
        QPoint targetPoint=this->_nextStep->getPosition();

        // 用向量确定移动方向
        QVector2D vectorToTarget(targetPoint-_position);
        vectorToTarget.normalize();
        _position += vectorToTarget.toPoint()*this->_speed;
        _rotationSprite = qRadiansToDegrees(qAtan2(vectorToTarget.y(), vectorToTarget.x())) + 180;
}

void Enemy::outOfRange(Tower0 *attacker){
    vector<Tower0*>::iterator it;
    it = find(_attackerTowers0.begin(), _attackerTowers0.end(), attacker);
    if (it == _attackerTowers0.end()){
        return;
    }
    else {
        this->_attackerTowers0.erase(it);
    }
}

void Enemy::outOfRange(Tower2 *attacker){
    vector<Tower2 *>::iterator it;
    it = find(_attackerTowers2.begin(), _attackerTowers2.end(), attacker);
    if (it == _attackerTowers2.end()){
        return;
    }
    else {
        this->_attackerTowers2.erase(it);
    }
}

void Enemy::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/mymusic/enemyDied.mp3"));
    player->setVolume(30);
    player->play();
}



/*

void Enemy::setSpeed()
{
    _speed = SPEED * 0.7;
}

void Enemy::upSpeed()
{
    _speed = SPEED;
}

void Enemy::upLevel()
{
    _level += 1;
}
*/


