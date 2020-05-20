#ifndef POSITION_H
#define POSITION_H
#include <vector>
using namespace std;
class Position
{
public:
    static int MAP_BLOCK_SIZE;
    static vector<Position> AVAILABLE_POSITION;
    static Position findPosition(int x, int y);

    Position(){}
    Position(int x, int y, bool available=true);
    Position(const Position &p);
    int getX() const{return this->_x;}
    int getY() const{return this->_y;}
    void setX(int x) {this->_x=x;}
    void setY(int y) {this->_y=y;}
    bool operator == (const Position &p) const;

private:
    int _x, _y;
    bool _isAvailable;
};

#endif // POSITION_H
