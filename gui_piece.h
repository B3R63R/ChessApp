#ifndef GUI_PIECE_H
#define GUI_PIECE_H
#include <QPushButton>
#include <QWidget>
#include <QFrame>
#include "chesslogic.h"
namespace GUI {

class Piece : public QPushButton
{
    Q_OBJECT
public:
    explicit Piece(LOGIC::Color color, QWidget *parent = nullptr);
    void setCurrentFrame(QFrame* frame);
    QFrame* getCurrentFrame();
    LOGIC::Color getColor();
private:
    QFrame* currentFrame;
    LOGIC::Color color;


};
}
#endif // GUI_PIECE_H


