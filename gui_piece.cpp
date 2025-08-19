#include "gui_piece.h"

GUI::Piece::Piece(QWidget *parent)
    : QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

