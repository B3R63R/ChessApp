#include "blackpiececlasses.h"
#include <QPushButton>

pawnBlack::pawnBlack(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/bP.png) 0 0 0 0 stretch stretch; border: none;");
    //this->setGeometry(80,80);
    //QIcon icon(":/resource/img/wP.png");
    //this->setIcon(icon);
    //this->setIconSize(QSize(50,50));
    //this->setStyleSheet("background-color: transparent; border: none;");

}

rookBlack::rookBlack(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/bR.png) 0 0 0 0 stretch stretch; border: none;");
}

bishopBlack::bishopBlack(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/bB.png) 0 0 0 0 stretch stretch; border: none;");
}

knightBlack::knightBlack(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/bN.png) 0 0 0 0 stretch stretch; border: none;");
}

queenBlack::queenBlack(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/bQ.png) 0 0 0 0 stretch stretch; border: none;");
}

kingBlack::kingBlack(QWidget *parent)
    : QPushButton(parent)
{

    this->setFixedSize(60, 60);
    this->setStyleSheet("background-image: url(:/resource/img/bK.png) 0 0 0 0 stretch stretch; border: none;");
}
