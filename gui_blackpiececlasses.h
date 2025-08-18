#ifndef GUI_BLACKPIECECLASSES_H
#define GUI_BLACKPIECECLASSES_H
#include "gui_piece.h"

namespace GUI {


class PawnBlack : public  GUI::Piece
{
public:
    explicit PawnBlack(QWidget *parent = nullptr);

};


class RookBlack : public  GUI::Piece
{
public:
    explicit RookBlack(QWidget *parent = nullptr);
};

class KnightBlack : public  GUI::Piece
{
public:
    explicit KnightBlack(QWidget *parent = nullptr);
};

class BishopBlack : public  GUI::Piece
{
public:
    explicit BishopBlack(QWidget *parent = nullptr);
};

class QueenBlack : public  GUI::Piece
{
public:
    explicit QueenBlack(QWidget *parent = nullptr);
};

class KingBlack : public  GUI::Piece
{
public:
    explicit KingBlack(QWidget *parent = nullptr);
};
}
#endif // GUI_BLACKPIECECLASSES_H
