#ifndef TOWER0_H
#define TOWER0_H
#include <QPoint>
#include <QPainter>
#include <QTimer>
#include <QVector2D>
#include "position.h"

class World;
class Enemy;

class Tower0 : QObject
{
    Q_OBJECT
public:
    static const int TOWER_SIZE;//攻击塔图标大小
    Tower0(QPoint position);
    ~Tower0();

    bool operator == (const Tower0 &t) {
            return (this->_position == t._position);
        }

    void show(QPainter *painter) const;

    void checkEnemyInRange();
    void startAttack();
    void setEnemy(Enemy *e);
    void targetDied();
    void enemyOutOfRange();

private slots:
    void shootWeapon();

protected:
    //攻击属性：
    int	_attackRange;//攻击范围
    int	_attackDamage;//伤害值
    int	_attackInterval;//攻击间隔
    QTimer * _attackTimer;//攻击计时器
    Enemy * _currentEnemy;//攻击目标
    World * _game;

    qreal _rotation;//旋转角度

    QPoint _position;//左上角坐标点
    QPoint _centrePosition;
    QPixmap _pixmap;//图标
};

#endif // TOWER0_H
