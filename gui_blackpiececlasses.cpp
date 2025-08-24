#include "gui_blackpiececlasses.h"
#include "gui_piece.h"

GUI::PawnBlack::PawnBlack(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{
    this->setStyleSheet(this->styleSheet() +"background-image: url(:/chessfontgioco/chessfonts/gioco/bP.svg);");
}

GUI::RookBlack::RookBlack(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bR.svg);");
}

GUI::BishopBlack::BishopBlack(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bB.svg);");
}

GUI::KnightBlack::KnightBlack(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{


    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bN.svg);");

}

GUI::QueenBlack::QueenBlack(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{

    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bQ.svg);");
}

GUI::KingBlack::KingBlack(LOGIC::Color color, QWidget *parent)
    : Piece(color, parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/chessfontgioco/chessfonts/gioco/bK.svg);");
}
