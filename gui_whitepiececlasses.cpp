#include "gui_whitepiececlasses.h"
#include "gui_piece.h"

GUI::PawnWhite::PawnWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/wP.png); border: none; background-repeat: no-repeat; background-position: center;");
    //this->setGeometry(80,80);
    //QIcon icon(":/resource/img/wP.png");
    //this->setIcon(icon);
    //this->setIconSize(QSize(50,50));
    //this->setStyleSheet("background-color: transparent; border: none;");

}

GUI::RookWhite::RookWhite(QWidget *parent)
    : Piece(parent)
{
    this->setStyleSheet("background-image: url(:/resource/img/wR.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::BishopWhite::BishopWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet("background-image: url(:/resource/img/wB.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::KnightWhite::KnightWhite(QWidget *parent)
    : Piece(parent)
{   
    this->setStyleSheet("background-image: url(:/resource/img/wN.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::QueenWhite::QueenWhite(QWidget *parent)
    : Piece(parent)
{  
    this->setStyleSheet("background-image: url(:/resource/img/wQ.png); border: none; background-repeat: no-repeat; background-position: center;");
}

GUI::KingWhite::KingWhite(QWidget *parent)
    : Piece(parent)
{ 
    this->setStyleSheet("background-image: url(:/resource/img/wK.png); border: none; background-repeat: no-repeat; background-position: center;");
}

