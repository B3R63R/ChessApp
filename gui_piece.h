#ifndef GUI_PIECE_H
#define GUI_PIECE_H
#include <QPushButton>
#include <QWidget>

namespace GUI {

class Piece : public QPushButton
{
    Q_OBJECT
public:
    explicit Piece(QWidget *parent = nullptr);

private:

};
}
#endif // GUI_PIECE_H


