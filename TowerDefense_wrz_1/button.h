#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>

class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(QPixmap pixmap);

signals:

};

#endif // BUTTON_H
