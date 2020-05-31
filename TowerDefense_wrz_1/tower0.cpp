#include "tower0.h"

const int Tower0::TOWER_SIZE=70;
//vector<Tower0 *> Tower0::TOWER0_VECTOR;

Tower0::Tower0(QPoint position):
    _range(100), _damage(10), _interval(1000), _position(position),
    _pixmap("/Users/shaner/Qt_files/TowerDefense_wrz_1/icons/tower1.png")
{

}

void Tower0::show(QPainter *painter) const
{
    painter->save();
    QPen pen(Qt::black, 1, Qt::DashLine);
    painter->setPen(pen);

    QPoint deltaP(TOWER_SIZE/2, TOWER_SIZE/2);//中心点与_position的偏移
    painter->translate(this->_position);//以_position（左上角点）作为坐标原点
    painter->drawEllipse(deltaP, this->_range, this->_range);//以中心点为圆心画圆来表示攻击范围
    painter->drawPixmap(0,0,Tower0::TOWER_SIZE, Tower0::TOWER_SIZE, _pixmap);
    painter->restore();
}
