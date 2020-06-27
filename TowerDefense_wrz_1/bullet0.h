#ifndef BULLET0_H
 #define BULLET0_H

 #include <QPoint>
 #include <QPixmap>
 #include <QObject>
 #include <QPainter>
 #include "enemy.h"

 class World;

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


 #endif // BULLET0_H
