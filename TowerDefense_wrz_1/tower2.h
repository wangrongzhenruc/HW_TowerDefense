#ifndef TOWER2_H
#define TOWER2_H
#include "tower0.h"
#include <QObject>


class Tower2: public Tower0
{
public:
    Tower2(QPoint position);
    ~Tower2();

    void blockEnemy();
    void checkEnemyInRange();
    void setEnemy(Enemy *enemy);
    void show(QPainter *painter) const;
    void enemyOutOfRange();


protected:
    QPixmap _pixmap;//图标
    World * _game;
};


#endif // TOWER2_H
