# HW_TowerDefense
塔防游戏大作业正式仓库
version3变动：
1.调试好了enemy类，可以（1）自动按波出动，（2）有血条，被打击后可以掉血，血光了之后消失，（3）如果有累计五个敌人达到我方阵地则游戏失败。
2.添加了bullet类，增加.h.和cpp文件，（1）可以按目标攻打敌人。
3.改动了tower类，（1）可以攻打范围内敌人。
4.改动了world类，添加BULLET_VECTOR容器储存子弹，并且画出子弹。
5.改动了mainwindow类，添加了游戏结束的函数，并且画了子弹。

具体变动：
1.enemy:

class Enemy : public QObject
{
    Q_OBJECT
public:
    static const int ENEMY_SIZE;
    static const int MAX_HP;
    static const int HP_LEN;
    static const int SPEED;

    Enemy(EnemyRoad *startPoint);
    ~Enemy();

    bool operator == (const Enemy &e) {
            return (this->_position == e._position);
        }

    friend class World;

    QPoint getPosition() const{return this->_position;}
    EnemyRoad * getNextPosition() const{return this->_nextStep;}

    void show(QPainter *painter) const;

    void move();
    void goOnNextPosition();

    void addAttacker(Tower0 *attacker){ _attackerTowers.push_back(attacker); }
    void outOfRange(Tower0 *attacker);

    //void setSpeed();
    //void upSpeed();
    //void upLevel();

public slots:
    void doActivate() { this->_active = true; }

protected:
    bool			_active;
    //int             m_level;
    int				_currentHP;
    double			_speed;
    double			_rotationSprite;

    QPoint			_position;
    EnemyRoad *		_nextStep;

    vector<Tower0 *> _attackerTowers;

    QPixmap _pixmap;//图标
};

2.bullet:

class Bullet0 : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPosition READ getCurrentPos WRITE setCurrentPos)

public:
    static const int BULLET_SIZE;

    Bullet0(QPoint startPos, QPoint targetPoint, int damage, Enemy *target);
    ~Bullet0();

    bool operator == (const Bullet0 &b) {
            return (this->_currentPosition == b._currentPosition &&
                    this->_target==b._target);
        }

    void show(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos) { this->_currentPosition=pos; }
    QPoint getCurrentPos() const { return this->_currentPosition; }

private slots:
    void hitTarget();

private:
    const QPoint	_startPosition;
    const QPoint	_targetPosition;
    const QPixmap	_pixmap;
    QPoint			_currentPosition;
    Enemy *			_target;
    World *	        _game;
    int				_damage;
};

3.tower:

    bool operator == (const Tower0 &t) {
            return (this->_position == t._position);
        }
    void checkEnemyInRange();
    void startAttack();
    void setEnemy(Enemy *e);
    void targetDied();
    void enemyOutOfRange();
    QTimer * _attackTimer;//攻击计时器
    Enemy * _currentEnemy;//攻击目标
    World * _game;
    
4.world:

    static vector<Bullet0 *> BULLET_VECTOR;
    static bool isLose;
    static bool isWin;
    void enenyMove(Enemy &enemy);
    void enemyDied(Enemy *enemy);
    void enemyDamaged(Enemy *enemy, int damage);
    bool _gameWin;
    int _baseHP;
    
5.mainwindow:

void MainWindow::updateMap(){
//添加
    int n2 = World::TOWER_VECTOR.size();
    for (int i=0;i<n2;i++){
        World::TOWER_VECTOR[i]->checkEnemyInRange();
    }

}

void MainWindow::paintEvent(QPaintEvent *){
//添加
    int n3 = World::BULLET_VECTOR.size();
    for (int i=0;i<n3;i++){
        World::BULLET_VECTOR[i]->show(frontPainter);
    }
}


    