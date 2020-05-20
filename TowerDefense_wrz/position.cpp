#include "position.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;

int Position::MAP_BLOCK_SIZE=80;
vector<Position> Position::AVAILABLE_POSITION= [] {
    vector<Position> v;
    char fileName[100]="/Users/shaner/Qt_files/cpp_sem2/TowerDefense_wrz/map1_position.csv";
    ifstream in(fileName);//打开文件
    string line;
    if(in) // 有该文件
        {
            while (getline (in, line)) // line中不包括每行的换行符
            {
                int x,y;
                x=line[0]-48; y=line[2]-48;
                v.push_back(Position(x, y,true));
            }
        }
        else // 没有该文件
        {
            cout <<"no such file" << endl;
        }
    return v;
}();

//static Position findPosition(int x, int y);

Position::Position(int x, int y, bool available):
    _x(x),_y(y),_isAvailable(available){}
Position::Position(const Position &p):
    _x(p._x), _y(p._y){}

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

