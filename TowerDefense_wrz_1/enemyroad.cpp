#include "enemyroad.h"
#include <QPainter>
#include <QColor>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
vector<EnemyRoad *> EnemyRoad::ROADPOINT_VECTOR=[] {
    vector<EnemyRoad *> v;
    EnemyRoad *EnemyRoad1 = new EnemyRoad(QPoint(865, 255));
    ROADPOINT_VECTOR.push_back(EnemyRoad1);
    EnemyRoad1->_nextPoint=NULL;

    char fileName[100]="/Users/shaner/Qt_files/TowerDefense_wrz_1/enemyroad.csv";
    ifstream in(fileName);//打开文件
    string line;
    if(in) // 有该文件
        {
            while (getline (in, line)) // line中不包括每行的换行符
            {
                string strX, strY;
                strX=line.substr(0,line.find(','));
                strY=line.substr(line.find(',')+1,line.length()-line.find(' ')-1);
                EnemyRoad *enemyroadpoint = new EnemyRoad(QPoint(stoi(strX), stoi(strY)));
                enemyroadpoint->setNextPoint(v.back());
                v.push_back(enemyroadpoint);

            }
        }
        else // 没有该文件
        {
            cout <<"no such file" << endl;
        }

    return v;
}();


EnemyRoad::EnemyRoad(QPoint pos):
    _position(pos), _nextPoint(NULL) {}

void EnemyRoad::setNextPoint(EnemyRoad *nextPoint)
{
    _nextPoint = nextPoint;
}

/*void EnemyRoad::show(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::green);
    painter->drawEllipse(_position, 6, 6);
    painter->drawEllipse(_position, 2, 2);

    if (_nextPoint)
        painter->drawLine(_position, _nextPoint->_position);
    painter->restore();
}*/


