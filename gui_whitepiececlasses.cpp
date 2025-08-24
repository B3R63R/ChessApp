#include "gui_whitepiececlasses.h"
#include "gui_piece.h"

GUI::PawnWhite::PawnWhite(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wP.svg);");
}

GUI::RookWhite::RookWhite(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wR.svg);");
}

GUI::BishopWhite::BishopWhite(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{ 
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wB.svg);");
}

GUI::KnightWhite::KnightWhite(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{   
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wN.svg);");
}

GUI::QueenWhite::QueenWhite(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wQ.svg);");

}

GUI::KingWhite::KingWhite(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{ 
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/wK.svg);");
}

