#include "world.h"
#include <math.h>

World::World()
{

}

void World::setTower(const QPoint &p){
    vector<Position>::iterator it; //迭代器
    it = Position::AVAILABLE_POSITION.begin();
    while(it!=Position::AVAILABLE_POSITION.end()){
        bool flag1 = (*it).inArea(p);
        bool flag2 = (*it).isAvailable();
        if (flag1 && flag2){
            (*it).setAvailable(false);
            Tower0 *tower = new Tower0((*it).getPoint());
            _towerVector.push_back(tower);
            break;
         }
        else{
            it++;
        }
    }
}


/*bool World::areCirclesMeet(QPoint point1, int radius1, QPoint point2, int radius2)
{
    double xDis = point1.x()-point2.x();
    double yDis = point1.y()-point2.y();
    double distance = sqrt(xDis*xDis + yDis*yDis);
    if (distance <= radius1 + radius2){
        return true;
    }
    return false;
}

void World::enenyMove(Enemy &enemy){
    if (areCirclesMeet(enemy.getPosition(), Enemy::SPEED,
                       enemy.getNextPosition()->getPosition(), Enemy::SPEED))
    {
        // 敌人抵达了一个航点
        if (enemy.getNextPosition()->getNextPoint())
        {
            // 还有下一个航点
            enemy.goOnNextPosition();
        }
        else
        {
            // 进入基地
            //m_game->getHpDamage();
             vector<Enemy*>::iterator it;
             it = _enemyVector.begin()+
            this->_enemyVector.erase(&enemy);
            return;
        }
    }
    int x =  this->_player->getNextX(direction);
    int y = this->_player->getNextY(direction);
    this->eraseObj(x,y);
    //移动玩家
    this->_player->move(direction, steps);
}*/



