#include "bullet0.h"
#include "world.h"
#include <QPropertyAnimation>

const int Bullet0::BULLET_SIZE=1;

Bullet0::Bullet0(QPoint startPos, QPoint targetPoint, int damage, Enemy *target)
    : _startPosition(startPos-QPoint(BULLET_SIZE,BULLET_SIZE))
    , _targetPosition(targetPoint-QPoint(BULLET_SIZE,BULLET_SIZE))
    , _pixmap(":/myicons/bullet1.png")
    , _currentPosition(startPos-QPoint(BULLET_SIZE,BULLET_SIZE))
    , _target(target)
    , _damage(damage)
{
    _game=new World;
}

Bullet0::~Bullet0(){
    delete _game;
}

void Bullet0::show(QPainter *painter) const
{
    painter->drawPixmap(_currentPosition, _pixmap);
}

void Bullet0::move()
{
    // 300毫秒内击中敌人
    static const int duration = 300;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "_currentPosition");
    animation->setDuration(duration);
    animation->setStartValue(_startPosition);
    animation->setEndValue(_targetPosition);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet0::hitTarget()
{
    // 判断敌人是否还有效
    vector<Enemy*>::iterator it;
    it = find(World::ENEMY_VECTOR.begin(), World::ENEMY_VECTOR.end() , _target);
    if (it!= World::ENEMY_VECTOR.end() ){
        _game->enemyDamaged(*it, _damage);
        _game->eraseBullet(this);
    }
    else{
        _game->eraseBullet(this);
    }
}





