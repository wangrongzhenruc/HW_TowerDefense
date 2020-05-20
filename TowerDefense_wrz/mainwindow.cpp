#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    QPixmap pixmap("/Users/shaner/Qt_files/cpp_sem2/TowerDefense_wrz/icons_2/map1.png");
    painter->drawPixmap(pixmap.rect(), pixmap);
    painter->end();
    delete painter;
}


