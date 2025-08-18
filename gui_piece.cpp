#include "gui_piece.h"

GUI::Piece::Piece(QWidget *parent)
    : QPushButton(parent)
{
    this->setFixedSize(60, 60);
    this->setStyleSheet("border: none;");


}

