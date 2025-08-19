#include "gui_blackpiececlasses.h"
#include "gui_piece.h"

GUI::PawnBlack::PawnBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bP.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::RookBlack::RookBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bR.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::BishopBlack::BishopBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bB.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::KnightBlack::KnightBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bN.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::QueenBlack::QueenBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet("background-image: url(:/resource/img/bQ.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::KingBlack::KingBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/bK.png); border: none; background-repeat: no-repeat; background-position: center;");
}
