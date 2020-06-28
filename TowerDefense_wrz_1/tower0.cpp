#include "tower0.h"
#include "enemy.h"
#include "world.h"
#include "bullet0.h"
#include <QtMath>

bool Tower0::areCirclesMeet(QPoint point1, int radius1, QPoint point2, int radius2)
{
    double xDis = point1.x()-point2.x();
    double yDis = point1.y()-point2.y();
    double distance = sqrt(xDis*xDis + yDis*yDis);
    if (distance <= radius1 + radius2){
        return true;
    }
    return false;
}

const int Tower0::TOWER_SIZE=70;

Tower0::Tower0(QPoint position):
      _attackRange(100)
    , _attackDamage(10)
    , _attackInterval(100)
    , _currentEnemy(NULL)
    , _position(position)
    , _centrePosition(position+QPoint(TOWER_SIZE/2, TOWER_SIZE/2))
    , _pixmap(":/myicons/tower1.png")
{
    _game=new World;// 创建World对象

    _attackTimer = new QTimer(this);// 创建计时器
    connect(_attackTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
    // 设置了槽与信号函数的连接，但还未启动
}

Tower0::~Tower0(){
    delete _game;
}

void Tower0::show(QPainter *painter) const
{
    painter->save();
    QPen pen(Qt::black, 1, Qt::DashLine);
    painter->setPen(pen);

    QPoint deltaP(TOWER_SIZE/2, TOWER_SIZE/2);//中心点与_position的偏移
    painter->translate(this->_position);//以_position（左上角点）作为坐标原点
    painter->drawEllipse(deltaP, this->_attackRange, this->_attackRange);//以中心点为圆心画圆来表示攻击范围
    painter->drawPixmap(0,0,Tower0::TOWER_SIZE, Tower0::TOWER_SIZE, _pixmap);
    painter->restore();
}

void Tower0::updatePixmap(){
    this->_pixmap.load(":/myicons/tower1.2.png");
}

void Tower0::updateDamage(){
    this->_attackDamage = 1.5*_attackDamage;
    this->_attackRange = 1.2*_attackRange;
}

void Tower0::checkEnemyInRange()
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



void Tower0::startAttack(){
    _attackTimer->start(_attackInterval);// 计时器开始
}

void Tower0::setEnemy(Enemy *enemy){
    _currentEnemy=enemy;// 设置目标敌人
    startAttack();// 开始进攻
    _currentEnemy->addAttacker(this);// 为敌人添加攻击者
}

void Tower0::shootWeapon()
{
    Bullet0 *bullet = new Bullet0(this->_centrePosition, this->_currentEnemy->getPosition()
                                  , this->_attackDamage, this->_currentEnemy);
    bullet->move();
    World::BULLET_VECTOR.push_back(bullet);
}

void Tower0::targetDied(){
    if(_currentEnemy){
        _currentEnemy=NULL;
    }
    this->_attackTimer->stop();
}

void Tower0::enemyOutOfRange(){
    this->_currentEnemy->outOfRange(this);
    if(_currentEnemy){
        _currentEnemy=NULL;
    }
    this->_attackTimer->stop();
}

void Tower0::onSet(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/mymusic/setTower.mp3"));
    player->setVolume(30);
    player->play();
}
