#include "tower2.h"
#include "world.h"

Tower2::Tower2(QPoint position):
    Tower0(position)
    , _pixmap(":/myicons/tower2.png")
{
    _game=new World;

    _attackTimer = new QTimer(this);
    //connect(_attackTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower2::~Tower2(){
    delete _game;
}

void Tower2::show(QPainter *painter) const
{
    painter->save();
    QPen pen(Qt::black, 1, Qt::DashLine);
    painter->setPen(pen);

    painter->translate(this->_position);//以_position（左上角点）作为坐标原点
    painter->drawPixmap(0,0,Tower0::TOWER_SIZE, Tower0::TOWER_SIZE, _pixmap);
    painter->restore();
}

void Tower2::checkEnemyInRange()
{
    if (_currentEnemy)
    {
        // 如果敌人脱离攻击范围
        if (!areCirclesMeet(_centrePosition, _attackRange
                            , _currentEnemy->getPosition(), 1)){
            enemyOutOfRange();
        }
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        int n = World::ENEMY_VECTOR.size();
        for (int i=0;i<n;i++){
            if(areCirclesMeet(_centrePosition, _attackRange
                              , World::ENEMY_VECTOR[i]->getPosition(), 1))
            {
                setEnemy(World::ENEMY_VECTOR[i]);
                break;
            }
        }
    }
}

void Tower2::setEnemy(Enemy *enemy){
    _currentEnemy=enemy;
    //startAttack();
    enemy->setSpeed(0.5);
    enemy->setShowBlock(true);
    _currentEnemy->addAttacker(this);
}

void Tower2::enemyOutOfRange(){
    this->_currentEnemy->outOfRange(this);
    this->_currentEnemy->setSpeed(Enemy::SPEED);
    this->_currentEnemy->setShowBlock(false);
    if(_currentEnemy){
        _currentEnemy=NULL;
    }
}

