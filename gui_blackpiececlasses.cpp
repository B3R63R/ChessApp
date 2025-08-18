#include "gui_blackpiececlasses.h"
#include "gui_piece.h"

GUI::PawnBlack::PawnBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bP.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::RookBlack::RookBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bR.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::BishopBlack::BishopBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bB.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::KnightBlack::KnightBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bN.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::QueenBlack::QueenBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bQ.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::KingBlack::KingBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bK.png) 0 0 0 0 stretch stretch; border: none;");
}
