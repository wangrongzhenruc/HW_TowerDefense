#include "mainwindow.h"
#include "startwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    StartWindow s;
    s.show();

    return a.exec();
}
