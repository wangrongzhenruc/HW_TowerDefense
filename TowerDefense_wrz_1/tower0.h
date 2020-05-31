#ifndef TOWER0_H
#define TOWER0_H
#include <QPoint>
#include <QPainter>
#include "position.h"
class Tower0
{
public:
    static const int TOWER_SIZE;//攻击塔图标大小
    //static vector<Tower0 *> TOWER0_VECTOR;//所有塔数组

    //Tower0(){};
    Tower0(QPoint position);

    void show(QPainter *painter) const;
protected:
    int	_range;//攻击范围
    int	_damage;//伤害值
    int	_interval;//攻击间隔
    //qreal _rotation;//旋转角度

    const QPoint _position;//左上角坐标点
    const QPixmap _pixmap;//图标
};

#endif // TOWER0_H
