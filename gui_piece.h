#ifndef GUI_PIECE_H
#define GUI_PIECE_H
#include <QPushButton>
#include <QWidget>
#include <QFrame>
namespace GUI {

class Piece : public QPushButton
{
    Q_OBJECT
public:
    explicit Piece(QWidget *parent = nullptr);
    void setCurrentFrame(QFrame* frame);
    QFrame* getCurrentFrame();

private:
    QFrame* currentFrame;
};
}

#endif // GUI_PIECE_H


