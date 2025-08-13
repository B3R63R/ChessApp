#include "whitepiececlasses.h"
#include <QPushButton>


pawnWhite::pawnWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/wP.png) 0 0 0 0 stretch stretch; border: none;");
    //this->setGeometry(80,80);
    //QIcon icon(":/resource/img/wP.png");
    //this->setIcon(icon);
    //this->setIconSize(QSize(50,50));
    //this->setStyleSheet("background-color: transparent; border: none;");

}

rookWhite::rookWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/wR.png) 0 0 0 0 stretch stretch; border: none;");
}

bishopWhite::bishopWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/wB.png) 0 0 0 0 stretch stretch; border: none;");
}

knightWhite::knightWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/wN.png) 0 0 0 0 stretch stretch; border: none;");
}

queenWhite::queenWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/wQ.png) 0 0 0 0 stretch stretch; border: none;");
}

kingWhite::kingWhite(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/wK.png) 0 0 0 0 stretch stretch; border: none;");
}
