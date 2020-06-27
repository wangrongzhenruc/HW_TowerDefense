# HW_TowerDefense
塔防游戏大作业正式仓库
version4变动：
1.添加了tower2类，继承tower1，作为冷冻塔，可以使目标内敌人降速。
2.添加了startwindow类，作为开场画面进行过渡。
3.添加了button类，在窗口上添加按钮。
4.改动了main.cpp类，更改窗口调用。

具体变动：
1.tower2:

class Tower2: public Tower0
{
public:
    Tower2(QPoint position);
    ~Tower2();

    void blockEnemy();
    void checkEnemyInRange();
    void setEnemy(Enemy *enemy);
    void show(QPainter *painter) const;
    void enemyOutOfRange();


protected:
    QPixmap _pixmap;//图标
};

2.startwindow:

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    void paintEvent(QPaintEvent *e);

private:
    Ui::StartWindow *ui;
    QPixmap _backGround;
    QPixmap _startButton;
    QPixmap _quitButton;
};

3.button:

 class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(QPixmap pixmap);

signals:

};
4.main.cpp:

    //MainWindow w;
    StartWindow s;

    