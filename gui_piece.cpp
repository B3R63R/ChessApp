#include "gui_piece.h"

GUI::Piece::Piece(QWidget *parent)
    : QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet(" border: none; "
                        "background-repeat: no-repeat; "
                        "background-position: center;");

}

