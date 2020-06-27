#include "button.h"

Button::Button(QPixmap pix):QPushButton(0)
{
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}
