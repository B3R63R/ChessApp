#include "gui_whitepiececlasses.h"
#include "Piece.h"

namespace GUI {
GUI::PawnWhite::PawnWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/wP.png) 0 0 0 0 stretch stretch; border: none;");
    //this->setGeometry(80,80);
    //QIcon icon(":/resource/img/wP.png");
    //this->setIcon(icon);
    //this->setIconSize(QSize(50,50));
    //this->setStyleSheet("background-color: transparent; border: none;");

}

GUI::RookWhite::RookWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/wR.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::BishopWhite::BishopWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet("background-image: url(:/resource/img/wB.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::KnightWhite::KnightWhite(QWidget *parent)
    : Piece(parent)
{   
    this->setStyleSheet("background-image: url(:/resource/img/wN.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::QueenWhite::QueenWhite(QWidget *parent)
    : Piece(parent)
{  
    this->setStyleSheet("background-image: url(:/resource/img/wQ.png) 0 0 0 0 stretch stretch; border: none;");
}

GUI::KingWhite::KingWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet("background-image: url(:/resource/img/wK.png) 0 0 0 0 stretch stretch; border: none;");
}

}
