#ifndef PIECE_H
#define PIECE_H
#include <QPushButton>
#include <QWidget>

class piece : public QPushButton
{
    Q_OBJECT
public:
    piece(QWidget *parent = 0);

    int getCurrentRow() const;
    int getCurrentCol() const;

    void setPosition(int row, int col);

private:
    int currentRow;
    int currentCol;
};
#endif // PIECE_H

