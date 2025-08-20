#include "gui_blackpiececlasses.h"
#include "gui_piece.h"

GUI::PawnBlack::PawnBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() +"background-image: url(:/chessfontgioco/chessfonts/gioco/bP.svg);");
}

GUI::RookBlack::RookBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bR.svg);");
}

GUI::BishopBlack::BishopBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bB.svg);");
}

GUI::KnightBlack::KnightBlack(QWidget *parent)
    : Piece(parent)
{


    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bN.svg);");

}

GUI::QueenBlack::QueenBlack(QWidget *parent)
    : Piece(parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bQ.svg);");
}

GUI::KingBlack::KingBlack(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bK.svg);");
}
