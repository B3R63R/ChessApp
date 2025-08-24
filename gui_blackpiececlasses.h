#ifndef GUI_BLACKPIECECLASSES_H
#define GUI_BLACKPIECECLASSES_H
#include "gui_piece.h"

namespace GUI {


class PawnBlack : public  GUI::Piece
{
public:
    explicit PawnBlack(LOGIC::Color color, QWidget *parent = nullptr);

};


class RookBlack : public  GUI::Piece
{
public:
    explicit RookBlack(LOGIC::Color color, QWidget *parent = nullptr);
};

class KnightBlack : public  GUI::Piece
{
public:
    explicit KnightBlack(LOGIC::Color color, QWidget *parent = nullptr);
};

class BishopBlack : public  GUI::Piece
{
public:
    explicit BishopBlack(LOGIC::Color color, QWidget *parent = nullptr);
};

class QueenBlack : public  GUI::Piece
{
public:
    explicit QueenBlack(LOGIC::Color color, QWidget *parent = nullptr);
};

class KingBlack : public  GUI::Piece
{
public:
    explicit KingBlack(LOGIC::Color color, QWidget *parent = nullptr);
};
}
#endif // GUI_BLACKPIECECLASSES_H
