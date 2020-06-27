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
    return false;
}

int World::chooseTowerType(const QPoint &p){
    Position tower1_p(5,150,false);
    Position tower2_p(5,350,false);
    if(tower1_p.inArea(p, 100, 100)){
        return 1;
    }
    if(tower2_p.inArea(p, 100, 100)){
        return 2;
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
                Tower0 *tower = new Tower0((*it).getPoint());
                TOWER_0_VECTOR.push_back(tower);
                tower->onSet();
                break;
            }
            else{
                this->PlayerGold -= Tower_2_Cost;
                (*it).setAvailable(false);
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


bool World::areCirclesMeet(QPoint point1, int radius1, QPoint point2, int radius2)
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
    vector<Enemy*>::iterator it;
    it = find(ENEMY_VECTOR.begin(), ENEMY_VECTOR.end(), enemy);
    if (it == ENEMY_VECTOR.end()){
        return;
    }
    else {
        enemy->onErase();
        delete (*it);
        this->ENEMY_VECTOR.erase(it);
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
    if (enemy->_attackerTowers0.empty()&&enemy->_attackerTowers2.empty()){
    }
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

