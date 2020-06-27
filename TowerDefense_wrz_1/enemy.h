#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QMediaPlayer>
#include "enemyroad.h"
#include "tower0.h"
#include "tower2.h"


class Enemy : public QObject
{
    Q_OBJECT
public:
    static const int ENEMY_SIZE;
    static const int MAX_HP;
    static const int HP_LEN;
    static const int SPEED;

    Enemy(EnemyRoad *startPoint, int type);
    ~Enemy();

    bool operator == (const Enemy &e) {
            return (this->_position == e._position);
        }

    friend class World;

    QPoint getPosition() const{return this->_position;}
    EnemyRoad * getNextPosition() const{return this->_nextStep;}
    int getType(){ return this->_type; }

    void show(QPainter *painter) const;
    void setShowBlock(bool isShow);

    void move();
    void goOnNextPosition();

    void addAttacker(Tower0 *attacker){ _attackerTowers0.push_back(attacker); }
    void addAttacker(Tower2 *attacker){ _attackerTowers2.push_back(attacker); }
    void outOfRange(Tower0 *attacker);
    void outOfRange(Tower2 *attacker);
    //void outOfRange(Tower0 *attacker){ attacker=NULL; }
    void setSpeed(double times) { _speed = times*_speed; }

    void onErase();

    //void setSpeed();
    //void upSpeed();
    //void upLevel();

public slots:
    void doActivate() { this->_active = true; }

protected:
    bool			_active;
    bool            _isBlock;
    int             _type;
    int				_currentHP;
    double			_speed;
    double			_rotationSprite;

    QPoint			_position;
    EnemyRoad *		_nextStep;

    vector<Tower0 *> _attackerTowers0;
    vector<Tower2 *> _attackerTowers2;

    QPixmap _pixmap;//图标
};

#endif // ENEMY_H

