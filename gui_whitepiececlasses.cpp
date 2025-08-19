#include "gui_whitepiececlasses.h"
#include "gui_piece.h"

GUI::PawnWhite::PawnWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/wP.png);");
}

GUI::RookWhite::RookWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/wR.png);");
}

GUI::BishopWhite::BishopWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/wB.png);");
}

GUI::KnightWhite::KnightWhite(QWidget *parent)
    : Piece(parent)
{   
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/wN.png);");
}

GUI::QueenWhite::QueenWhite(QWidget *parent)
    : Piece(parent)
{  
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/wQ.png);");
}

GUI::KingWhite::KingWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet(this->styleSheet() + "background-image: url(:/resource/img/wK.png);");
}

