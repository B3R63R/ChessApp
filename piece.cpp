#include "piece.h"

piece::piece(QWidget *parent)
    : QPushButton(parent)
{
    this->setFixedSize(60, 60);
    this->setStyleSheet("border: none;");


}

int piece::getCurrentRow() const {
    return currentRow;
}
int piece:: getCurrentCol() const {
    return currentCol;
}

void piece::setPosition(int row, int col) {
    currentRow = row;
    currentCol = col;
}
