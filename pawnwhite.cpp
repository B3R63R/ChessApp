#include "pawnwhite.h"
#include <QPushButton>


pawnWhite::pawnWhite(QWidget *parent)
    : QPushButton(parent)
{

    //setFixedSize(55, 55);
    //this->setGeometry(80,80);
    QIcon icon(":/resource/img/wP.png");
    this->setIcon(icon);
    this->setIconSize(QSize(30,30));
    //this->setStyleSheet("background-color: transparent; border: none;");
}
