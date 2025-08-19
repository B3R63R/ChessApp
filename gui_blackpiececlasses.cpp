#include "gui_blackpiececlasses.h"
#include "gui_piece.h"

GUI::PawnBlack::PawnBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/bP.png);");
}

GUI::RookBlack::RookBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/bR.png);");
}

GUI::BishopBlack::BishopBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/bB.png);");
}

GUI::KnightBlack::KnightBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/bN.png);");
}

GUI::QueenBlack::QueenBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/bQ.png);");
}

GUI::KingBlack::KingBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/bK.png);");
}
