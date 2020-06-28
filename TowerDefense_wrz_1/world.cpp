#include "world.h"
#include <math.h>
#include <QVector2D>
#include <QTimer>
#include <QObject>

vector<Tower0 *> World::TOWER_0_VECTOR;
vector<Tower2 *> World::TOWER_2_VECTOR;
vector<Enemy *> World::ENEMY_VECTOR;
vector<Bullet0 *> World::BULLET_VECTOR;
bool World::isLose = false;
bool World::isWin = false;
int World::Tower_1_Cost = 30;
int World::Tower_2_Cost = 40;
int World::Waves = 0;
int World::BaseHP = 5;
int World::PlayerGold = 100;
int World::RewardGold = 10;

World::World()
{

}

bool World::canBuyTower(int type) const
{
    if (type==1 && PlayerGold >= Tower_1_Cost){
        return true;
    }
    else if (type==2 && PlayerGold >= Tower_2_Cost) {
        return true;
    }
    else if (type==3 && PlayerGold >= 40) {
        return true;
    }
    return false;
}

int World::chooseTowerType(const QPoint &p){
    Position tower1_p(5,150,false);
    Position tower2_p(5,350,false);
    Position eraser_p(10,550,false);
    if(tower1_p.inArea(p, 150, 150)){
        return 1;
    }
    if(tower2_p.inArea(p, 150, 150)){
        return 2;
    }
    if(eraser_p.inArea(p, 80, 80)){
        return 3;
    }
    else
        return 0;
}
void World::setTower(const QPoint &p, int type){
    vector<Position>::iterator it; //迭代器
    it = Position::AVAILABLE_POSITION.begin();
    while(it!=Position::AVAILABLE_POSITION.end()){
        bool flag1 = (*it).inArea(p);
        bool flag2 = (*it).isAvailable();
        if (flag1 && flag2 && this->canBuyTower(type)){
            if(type == 1){
                this->PlayerGold -= Tower_1_Cost;
                (*it).setAvailable(false);
                (*it).setHasTowr1(true);
                (*it).setHasTower(true);
                Tower0 *tower = new Tower0((*it).getPoint());
                TOWER_0_VECTOR.push_back(tower);
                tower->onSet();
                break;
            }
            else{
                this->PlayerGold -= Tower_2_Cost;
                (*it).setAvailable(false);
                (*it).setHasTower(true);
                Tower2 *tower = new Tower2((*it).getPoint());
                TOWER_2_VECTOR.push_back(tower);
                tower->onSet();
                break;
            }
         }
        else{
            it++;
        }
    }
}

void World::eraseTower(const QPoint &p){
    vector<Position>::iterator it; //迭代器
    it = Position::AVAILABLE_POSITION.begin();
    while(it!=Position::AVAILABLE_POSITION.end()){
        bool flag1 = (*it).inArea(p);
        bool flag2 = (*it).isHasTower();
        bool notFound = true;
        if (flag1 && flag2){
            (*it).setHasTower(false);
            (*it).setAvailable(true);
            if(true){
                vector<Tower0 *>::iterator iter;
                iter = TOWER_0_VECTOR.begin();
                while(iter!=TOWER_0_VECTOR.end()){
                    if((*iter)->getPosition() == (*it)){
                        delete (*iter);
                        TOWER_0_VECTOR.erase(iter);
                        notFound = false;
                        break;
                    }
                    else{
                        iter++;
                    }
                }
            }
            if(notFound){
                vector<Tower2 *>::iterator iter;
                iter = TOWER_2_VECTOR.begin();
                while(iter!=TOWER_2_VECTOR.end()){
                    if((*iter)->getPosition() == (*it)){
                        delete (*iter);
                        (*iter)->updateDamage();
                        TOWER_2_VECTOR.erase(iter);
                        break;
                    }
                    else{
                        iter++;
                    }
                }
            }
         }
        else{
            it++;
        }
    }
}

void World::updateTower(const QPoint &p){
    vector<Position>::iterator it; //迭代器
    it = Position::AVAILABLE_POSITION.begin();
    while(it!=Position::AVAILABLE_POSITION.end()){
        bool flag1 = (*it).inArea(p);
        bool flag2 = (*it).isHasTowr1();
        if (flag1 && flag2 && this->canBuyTower(3)){
            this->PlayerGold -= 40;
            (*it).setHasTowr1(false);
            vector<Tower0 *>::iterator iter;
            iter = TOWER_0_VECTOR.begin();
            while(iter!=TOWER_0_VECTOR.end()){
                if((*iter)->getPosition() == (*it)){
                    (*iter)->updatePixmap();
                    (*iter)->updateDamage();
                    break;
                }
                else{
                    iter++;
                }
            }
         }
        else{
            it++;
        }
    }
}


bool World::areCirclesMeet(QPoint point1, int radius1, QPoint point2, int radius2) const
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
    if (!enemy._active)
        return;
    else{
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
                this->baseDamaged();
                this->eraseEnemy(&enemy);
                return;
            }
        }
        enemy.move();
        return;
    }
}

void World::eraseEnemy(Enemy *enemy){
    vector<Enemy*>::iterator it; // 创建迭代器
    it = find(ENEMY_VECTOR.begin(), ENEMY_VECTOR.end(), enemy);
        // 使用find函数和运算符重载搜寻对应对象
    if (it == ENEMY_VECTOR.end()){
        return;
    }
    else {
        enemy->onErase();
        delete (*it); // 释放内存
        this->ENEMY_VECTOR.erase(it); // 在容器中删除该位置
    }

    if (ENEMY_VECTOR.empty())
        {
            ++Waves; // 当前波数加1
            // 继续读取下一波
            if (!loadWave())
            {
                isWin = true;
            }
        }
}

void World::enemyDied(Enemy *enemy)
{
    // 若敌人死亡，需要告知他的所有攻击者，还敌人已不存在
    if (enemy->_attackerTowers0.empty()&&enemy->_attackerTowers2.empty()){
    }// 若敌人没有攻击者，则不任何事情
    else{
        int n1 = enemy->_attackerTowers0.size();
        for (int i=0;i<n1;i++){
            enemy->_attackerTowers0[i]->targetDied();
        }
        int n2 = enemy->_attackerTowers2.size();
        for (int i=0;i<n2;i++){
            enemy->_attackerTowers2[i]->targetDied();
        }
    }
    // 删除敌人
    eraseEnemy(enemy);
}

void World::enemyDamaged(Enemy *enemy, int damage)
{
    enemy->_currentHP -= damage;
    // 阵亡,需要移除
    if (enemy->_currentHP <= 0)
    {
        PlayerGold+=RewardGold;
        enemyDied(enemy);
    }
}

bool World::loadWave()
{
    if (Waves >= 5){
        return false;
    }
    else if(Waves == 0){
        EnemyRoad *startPoint = EnemyRoad::ROADPOINT_VECTOR.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 150, 1500, 3000, 4500, 6000 };
        for (int i = 0; i < 5; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 0);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        return true;
    }
    else if(Waves == 1){
        EnemyRoad *startPoint = EnemyRoad::ROADPOINT_VECTOR.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 150, 1200, 2200, 3100, 4000 };
        for (int i = 0; i < 5; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 0);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        return true;
    }
    else if(Waves == 2){
        EnemyRoad *startPoint = EnemyRoad::ROADPOINT_VECTOR.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 150, 1500, 3000, 4500, 6000 };
        for (int i = 0; i < 2; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 0);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        for (int i = 0; i < 2; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 1);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i+2], enemy, SLOT(doActivate()));
        }
        Enemy *enemy = new Enemy(startPoint, 0);
        World::ENEMY_VECTOR.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[4], enemy, SLOT(doActivate()));
        return true;
    }
    else if(Waves == 3){
        EnemyRoad *startPoint = EnemyRoad::ROADPOINT_VECTOR.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 150, 1200, 2200, 3100, 4000 };
        for (int i = 0; i < 1; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 0);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        for (int i = 0; i < 3; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 1);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i+1], enemy, SLOT(doActivate()));
        }
        Enemy *enemy = new Enemy(startPoint, 2);
        World::ENEMY_VECTOR.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[4], enemy, SLOT(doActivate()));
        return true;
    }
    else {
        EnemyRoad *startPoint = EnemyRoad::ROADPOINT_VECTOR.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 150, 1500, 3000, 4500, 6000 };
        for (int i = 0; i < 2; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 1);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        for (int i = 0; i < 2; ++i)
        {
            Enemy *enemy = new Enemy(startPoint, 2);
            World::ENEMY_VECTOR.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i+2], enemy, SLOT(doActivate()));
        }
        Enemy *enemy = new Enemy(startPoint, 1);
        World::ENEMY_VECTOR.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[4], enemy, SLOT(doActivate()));
        return true;
    }

}


void World::eraseBullet(Bullet0 *bullet)
{
    vector<Bullet0 *>::iterator it;
    it = find(BULLET_VECTOR.begin(), BULLET_VECTOR.end(), bullet);
    if (it == BULLET_VECTOR.end()){
        return;
    }
    else {
        delete (*it);
        this->BULLET_VECTOR.erase(it);
    }
}


void World::baseDamaged(int damage){
    this->BaseHP -= damage;
    if(this->BaseHP <= 0){
        gameOver();
    }
}

void World::gameOver(){
    if(!isLose){
        isLose = true;
    }
}

