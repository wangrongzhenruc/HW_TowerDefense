#include "startwindow.h"
#include "mainwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow),
    _backGround(":/myicons/backGround.jpg"),
    _startButton(":/myicons/startButton.png"),
    _quitButton(":/myicons/quitButton.png")
{
    ui->setupUi(this);
    MainWindow * gameWindow = new MainWindow;
    Button * startButton = new Button(this->_startButton);
    startButton->setParent(this);
    startButton->move(550,300);
    connect(startButton, &Button::clicked, this, [=](){
        this->close();
        gameWindow->show();
    });
    Button * quitButton = new Button(this->_quitButton);
    quitButton->setParent(this);
    quitButton->move(630,500);
    connect(quitButton, &Button::clicked, this, &QApplication::quit);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), _backGround);
}
