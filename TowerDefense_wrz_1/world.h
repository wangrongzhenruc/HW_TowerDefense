#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "tower0.h"
#include "tower2.h"
#include <QPoint>
#include "position.h"
#include "enemy.h"
#include <QTimer>
#include <QObject>
#include "bullet0.h"
using namespace std;

class World
{

public:
    World();

    static vector<Tower0 *> TOWER_0_VECTOR;
    static vector<Tower2 *> TOWER_2_VECTOR;
    static vector<Enemy *> ENEMY_VECTOR;
    static vector<Bullet0 *> BULLET_VECTOR;
    static bool isLose;
    static bool isWin;
    static int Tower_1_Cost;
    static int Tower_2_Cost;
    static int Waves;
    static int BaseHP;
    static int PlayerGold;
    static int RewardGold;

    bool canBuyTower(int type) const;
    void setTower(const QPoint &p, int type);
    int chooseTowerType(const QPoint &p);

    bool areCirclesMeet(QPoint point1, int radius1, QPoint point2, int radius2);
    void enenyMove(Enemy &enemy);
    void enemyDied(Enemy *enemy);
    void enemyDamaged(Enemy *enemy, int damage);
    void eraseEnemy(Enemy *enemy);
    bool loadWave();

    void eraseBullet(Bullet0 *bullet);

    void baseDamaged(int damage = 1);
    void gameOver();

};

#endif // WORLD_H
