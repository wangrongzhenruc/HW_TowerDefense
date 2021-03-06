#ifndef POSITION_H
#define POSITION_H
#include <vector>
#include <QPoint>
using namespace std;

class Position
{
public:
    static const int MAP_BLOCK_SIZE_X;
    static const int MAP_BLOCK_SIZE_Y;
    static vector<Position> AVAILABLE_POSITION;
    static Position findPosition(int x, int y);

    Position(){}
    Position(int x, int y, bool available=true);
    Position(const Position &p);

    QPoint getPoint() const{return QPoint(this->_x, this->_y);}
    void setX(int x) {this->_x=x;}
    void setY(int y) {this->_y=y;}
    void setAvailable(bool isAvailable=false){this->_isAvailable=isAvailable;}
    void setHasTowr1(bool hasTower1=true){this->_hasTower1=hasTower1;}
    bool isHasTowr1(){return this->_hasTower1;}
    void setHasTower(bool hasTower=true){this->_hasTower=hasTower;}
    bool isHasTower(){return this->_hasTower;}
    bool isAvailable() {return this->_isAvailable;}

    bool inArea(const QPoint &p, int xrange = MAP_BLOCK_SIZE_X, int yrange = MAP_BLOCK_SIZE_Y) const;
    bool operator == (const Position &p) const;

private:
    int _x, _y;
    bool _isAvailable;
    bool _hasTower1;
    bool _hasTower;
};

#endif // POSITION_H
