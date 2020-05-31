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
    bool isAvailable() {return this->_isAvailable;}

    bool inArea(const QPoint &p) const;
    bool operator == (const Position &p) const;

private:
    int _x, _y;
    bool _isAvailable;
};

#endif // POSITION_H
