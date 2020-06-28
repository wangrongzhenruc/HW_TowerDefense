#include "enemyroad.h"
#include <QPainter>
#include <QColor>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
vector<EnemyRoad *> EnemyRoad::ROADPOINT_VECTOR=[] {
    vector<EnemyRoad *> v;
    EnemyRoad *EnemyRoad1 = new EnemyRoad(QPoint(865, 255));
    ROADPOINT_VECTOR.push_back(EnemyRoad1);
    EnemyRoad1->_nextPoint=NULL;
    //读取文件方案1
    QFile file(":/myicons/enemyroad.txt");
    QTextStream in(&file);
    QString line;
    QStringList list;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!in.atEnd()) {
            line=in.readLine();
            list=line.split(",");

            EnemyRoad *enemyroadpoint = new EnemyRoad(QPoint(list.at(0).toInt()
                                                     , list.at(1).toInt()));
            enemyroadpoint->setNextPoint(v.back());
            v.push_back(enemyroadpoint);
        }
    }
    else // 没有该文件
      {
          cout <<"no such file" << endl;
      }
    //读取文件方案2
    /*
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
    }*/

    return v;
}();


EnemyRoad::EnemyRoad(QPoint pos):
    _position(pos), _nextPoint(NULL) {}

void EnemyRoad::setNextPoint(EnemyRoad *nextPoint)
{
    _nextPoint = nextPoint;
}


