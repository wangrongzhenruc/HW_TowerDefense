#ifndef ENEMYROAD_H
#define ENEMYROAD_H
#include <QPoint>
#include <QPainter>
#include <vector>
using namespace std;
// 敌人移动的航线
class EnemyRoad
{
public:
    static vector<EnemyRoad *> ROADPOINT_VECTOR;
    EnemyRoad(QPoint pos);
    EnemyRoad(){}

    void setNextPoint(EnemyRoad *nextPoint);
    EnemyRoad* getNextPoint() const{ return _nextPoint; }
    const QPoint getPosition() const{ return _position; }


private:
    const QPoint		_position;
    EnemyRoad *			_nextPoint;
};
#endif // ENEMYROAD_H
