#include "gui_whitepiececlasses.h"
#include "gui_piece.h"

GUI::PawnWhite::PawnWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wP.svg);");
}

GUI::RookWhite::RookWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wR.svg);");
}

GUI::BishopWhite::BishopWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wB.svg);");
}

GUI::KnightWhite::KnightWhite(QWidget *parent)
    : Piece(parent)
{   
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wN.svg);");
}

GUI::QueenWhite::QueenWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wQ.svg);");

}

GUI::KingWhite::KingWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wK.svg);");
}

