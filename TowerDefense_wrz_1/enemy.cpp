#include "enemy.h"
#include "mainwindow.h"
//#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>


const int Enemy::MAX_HP=500;
const int Enemy::HP_LEN=70;
const int Enemy::ENEMY_SIZE=70;
const int Enemy::SPEED=2;

Enemy::Enemy(EnemyRoad *startWayPoint)
    : QObject(0)
    //, m_level(level)
    , _active(false)
    , _currentHP(MAX_HP)
    , _speed(Enemy::SPEED)
    , _rotationSprite(0.0)
    , _position(startWayPoint->getPosition())
    , _nextStep(startWayPoint->getNextPoint())
    , _attackerTowers()
    , _pixmap(":/myicons/enemy_green1.png")
{
}

Enemy::~Enemy()
{
    _attackerTowers.clear();
    _nextStep = NULL;
    //m_game = NULL;
}

void Enemy::show(QPainter *painter) const{
    if (!_active)
        return;

    painter->save();
    QPoint deltaP(ENEMY_SIZE/2, ENEMY_SIZE/2);//中心点与_position的偏移
    painter->translate(this->_position-deltaP);//以左上角点作为坐标原点

    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);
    QRect HPBackRect(QPoint(0,-ENEMY_SIZE/4), QSize(HP_LEN, 5));
    painter->drawRect(HPBackRect);

    painter->setBrush(Qt::green);
    double length = (double(_currentHP)/double(MAX_HP))*double(HP_LEN);
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
    vector<Tower0 *>::iterator it;
    it = find(_attackerTowers.begin(), _attackerTowers.end(), attacker);
    if (it == _attackerTowers.end()){
        return;
    }
    else {
        //(*it)->onErase();
        //delete (*it);
        this->_attackerTowers.erase(it);
    }
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


