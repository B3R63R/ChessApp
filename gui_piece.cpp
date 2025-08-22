#include "gui_piece.h"

GUI::Piece::Piece(QWidget *parent)
    : QPushButton(parent)
{

    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setStyleSheet("border: none; "
                        "background-repeat: no-repeat; "
                        "background-position: center;"
                        "background-color: transparent;");

}

void GUI::Piece::setCurrentFrame(QFrame* frame) {
    currentFrame = frame;
}
QFrame* GUI::Piece::getCurrentFrame() {
    return currentFrame;
}

