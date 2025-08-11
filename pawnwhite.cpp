#include "pawnwhite.h"
#include <QPushButton>


pawnWhite::pawnWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    //this->setGeometry(80,80);
    //QIcon icon(":/resource/img/wP.png");
    //this->setIcon(icon);
    //this->setIconSize(QSize(50,50));
    //this->setStyleSheet("background-color: transparent; border: none;");
    this->setStyleSheet("background-image: url(:/resource/img/wP.png) 0 0 0 0 stretch stretch; border: none;");
}
