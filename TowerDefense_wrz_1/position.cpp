#include "position.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
using namespace std;

const int Position::MAP_BLOCK_SIZE_X=74;
const int Position::MAP_BLOCK_SIZE_Y=78;
vector<Position> Position::AVAILABLE_POSITION = [] {
    vector<Position> v;
    //读取文件方案1
    QFile file(":/myicons/enemyroad.txt");
    QTextStream in(&file);
    QString line;
    QStringList list;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!in.atEnd()) {
            line=in.readLine();
            list=line.split(",");

            int x=list.at(0).toInt();
            int y=list.at(1).toInt();
            v.push_back(Position(x, y,true));
        }
    }
    else // 没有该文件
      {
          cout <<"no such file" << endl;
      }
    //读取文件方案2
    /*
    char fileName[100]="/Users/shaner/Qt_files/TowerDefense_wrz_1/map1_position.csv";
    ifstream in(fileName);//打开文件
    string line;
    if(in) // 有该文件
        {
            while (getline (in, line)) // line中不包括每行的换行符
            {
                string strX, strY;
                strX=line.substr(0,line.find(','));
                strY=line.substr(line.find(',')+1,line.length()-line.find(' ')-1);
                int x=stoi(strX)*MAP_BLOCK_SIZE_X;
                int y=stoi(strY)*MAP_BLOCK_SIZE_Y;
                v.push_back(Position(x, y,true));
            }
        }
        else // 没有该文件
        {
            cout <<"no such file" << endl;
        }*/
    return v;
}();


Position::Position(int x, int y, bool available):
    _x(x),_y(y),_isAvailable(available)
  ,_hasTower1(false),_hasTower(false){}

Position::Position(const Position &p):
    _x(p._x), _y(p._y), _isAvailable(p._isAvailable){}

bool Position::operator == (const Position &p) const{
    return (this->_x==p._x&&this->_y==p._y);
}

Position Position::findPosition(int x, int y){
    vector<Position>::iterator it;
    it = find (AVAILABLE_POSITION.begin(), AVAILABLE_POSITION.end(), Position(x, y));
    if (it == AVAILABLE_POSITION.end()){
        cout<<"Error: cannot find ICON"<<endl;
        return Position();
    }
    else{
        return (*it);
    }
}

bool Position::inArea(const QPoint &p, int xrange, int yrange) const
{
    bool xIn = p.x() >= this->_x && p.x() <= this->_x+ xrange;
    bool yIn = p.y() >= this->_y && p.y() <= this->_y+ yrange;
    return xIn && yIn;
}



