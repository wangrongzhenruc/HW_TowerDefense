#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "tower0.h"
#include <QPoint>
#include "position.h"
#include "enemy.h"
using namespace std;

class World
{
public:
    World();
    void setTower(const QPoint &p);
    void show(QPainter * painter);
    vector<Tower0 *> _towerVector;
    //vector<Enemy *> _enemyVector;
    //bool areCirclesMeet(QPoint point1, int radius1, QPoint point2, int radius2);
    //void enenyMove(Enemy &enemy);
private:

};

#endif // WORLD_H
