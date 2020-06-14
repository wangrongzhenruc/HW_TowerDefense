#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include "enemyroad.h"
#include "tower0.h"


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

#endif // ENEMY_H

