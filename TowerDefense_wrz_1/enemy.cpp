/*#include "enemy.h"
#include <QVector2D>
const int Enemy::MAX_HP=50;
const int Enemy::HP_LEN=80;
const int Enemy::ENEMY_SIZE=80;
const int Enemy::SPEED=3;

Enemy::Enemy(EnemyRoad *startPoint):
_currentHP(MAX_HP), _speed(SPEED), _position(startPoint->getPosition()),
_nextStep(startPoint->getNextPoint()),
  _pixmap("/Users/shaner/Qt_files/TowerDefense_wrz_1/icons_2/enemy_green1.png")
{
}

void Enemy::show(QPainter *painter) const{
    painter->save();
    QPoint deltaP(ENEMY_SIZE/2, ENEMY_SIZE/2);//中心点与_position的偏移
    painter->translate(this->_position-deltaP);//以左上角点作为坐标原点

    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);
    QRect HPBackRect(QPoint(0,-ENEMY_SIZE/4), QSize(HP_LEN, 5));
    painter->drawRect(HPBackRect);

    painter->setBrush(Qt::green);
    QRect HPFrontRect(QPoint(0,-ENEMY_SIZE/4), QSize(_currentHP/MAX_HP*HP_LEN, 5));
    painter->drawRect(HPFrontRect);

    painter->drawPixmap(0,0,Enemy::ENEMY_SIZE, Enemy::ENEMY_SIZE, _pixmap);
    painter->restore();
}

void Enemy::move(){
        QPoint targetPoint=this->_nextStep->getPosition();

        // 用向量确定移动方向
        QVector2D vectorToTarget(targetPoint-_position);
        vectorToTarget.normalize();
        _position += vectorToTarget.toPoint()*this->_speed;
}

void Enemy::goOnNextPosition(){
    this->_position = this->_nextStep->getPosition();
    this->_nextStep = this->_nextStep->getNextPoint();
}

void Enemy::hurt(int hurtAmount){

}*/

