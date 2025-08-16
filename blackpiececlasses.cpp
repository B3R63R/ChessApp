#include "blackpiececlasses.h"
#include "piece.h"

pawnBlack::pawnBlack(QWidget *parent)
    : piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bP.png) 0 0 0 0 stretch stretch; border: none;");
}

rookBlack::rookBlack(QWidget *parent)
    : piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bR.png) 0 0 0 0 stretch stretch; border: none;");
}

bishopBlack::bishopBlack(QWidget *parent)
    : piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bB.png) 0 0 0 0 stretch stretch; border: none;");
}

knightBlack::knightBlack(QWidget *parent)
    : piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bN.png) 0 0 0 0 stretch stretch; border: none;");
}

queenBlack::queenBlack(QWidget *parent)
    : piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bQ.png) 0 0 0 0 stretch stretch; border: none;");
}

kingBlack::kingBlack(QWidget *parent)
    : piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bK.png) 0 0 0 0 stretch stretch; border: none;");
}
