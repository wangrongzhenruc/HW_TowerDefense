#ifndef ENEMY_H
#define ENEMY_H
#include <QPoint>
#include <QPainter>
#include "enemyroad.h"
#include "tower0.h"

class Enemy
{
/*public:
    static const int ENEMY_SIZE;
    static const int MAX_HP;
    static const int HP_LEN;
    static const int SPEED;

    Enemy(EnemyRoad *startPoint);

    void show(QPainter *painter) const;
    void move();
    void hurt(int hurtAmount);
    QPoint getPosition() const{return this->_position;}
    void goOnNextPosition();
    EnemyRoad * getNextPosition() const{return this->_nextStep;}


private:

    int	_currentHP;
    int _speed;
    //double _rotation;

    QPoint			_position;
    EnemyRoad *		_nextStep;

    const QPixmap _pixmap;//图标*/

};

#endif // ENEMY_H
