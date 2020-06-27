#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include "button.h"

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

#endif // STARTWINDOW_H
