# HW_TowerDefense
塔防游戏大作业正式仓库
version4变动：
1.改动了world和mainwindow类，（1）增加拆除防御塔的功能，（2）使树塔可以双击升级。
2.改动了mainwindow类，界面画面呈现了敌人的类型表。

具体变动：
1.world:
.h:
void updateTower(const QPoint &p);
void eraseTower(const QPoint &p);
.cpp:
bool World::canBuyTower(int type) const
{
//未变动代码省略
    else if (type==3 && PlayerGold >= 40) {
        return true;
        }
//未变动代码省略
}

int World::chooseTowerType(const QPoint &p){
//未变动代码省略
    Position eraser_p(10,550,false);
    if(eraser_p.inArea(p, 80, 80)){
        return 3;
    }
//未变动代码省略
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

2.MainWindow:

.h:
    void mouseDoubleClickEvent(QMouseEvent *e);
.cpp:
void MainWindow::mouseDoubleClickEvent(QMouseEvent *e){
    QPoint pressPos = e->pos();
    _game.updateTower(pressPos);
    this->update();
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
//未变动代码省略
    else if(_game.chooseTowerType(pressPos)==3){
        towerType += 100;
    }
    else if(towerType==1||towerType==2){
        _game.setTower(pressPos, towerType);
    }
    else if(towerType==102||towerType==101){
        _game.eraseTower(pressPos);
    }
//未变动代码省略
}
