# HW_TowerDefense
塔防游戏大作业正式仓库
1.调试好了tower类，可以按地图放置攻击塔，并通过圆圈显示塔的范围。
2.添加了enemyroad类，增加.h.cpp文件，规划敌人行走路线。
3.enemy类只实现了初步，增加.h.cpp文件，没有完全调好，因此先注释掉。
4.添加了world类，增加.h.cpp文件，管理游戏。

具体变动：
1.调试好void MainWindow::mousePressEvent(QMouseEvent *e)；
  增加void World::setTower(const QPoint &p)；
  在mainwindow paintEvent中增加    
    int n1 = _game._towerVector.size();
      for (int i=0;i<n1;i++){
          _game._towerVector[i]->show(frontPainter);
      }
2.enemyroad:
  class EnemyRoad
  {
  public:
      static vector<EnemyRoad *> ROADPOINT_VECTOR;
      EnemyRoad(QPoint pos);
      EnemyRoad(){}
  
      void setNextPoint(EnemyRoad *nextPoint);
      EnemyRoad* getNextPoint() const{ return _nextPoint; }
      const QPoint getPosition() const{ return _position; }
  
  private:
      const QPoint		_position;
      EnemyRoad *			_nextPoint;
  };
4.world:
class World
{
public:
    World();
    void setTower(const QPoint &p);
    void show(QPainter * painter);
    vector<Tower0 *> _towerVector;

};