#ifndef GUI_WHITEPIECECLASSES_H
#define GUI_WHITEPIECECLASSES_H
#include <QPushButton>
#include "gui_piece.h"

namespace GUI {

class PawnWhite : public GUI::Piece
{
public:
    explicit PawnWhite(LOGIC::Color color, QWidget *parent = nullptr);
};


class RookWhite : public GUI::Piece
{
public:
    explicit RookWhite(LOGIC::Color color, QWidget *parent = nullptr);
};

class KnightWhite : public GUI::Piece
{
public:
    explicit KnightWhite(LOGIC::Color color, QWidget *parent = nullptr);
};

class BishopWhite : public GUI::Piece
{
public:
    explicit BishopWhite(LOGIC::Color color, QWidget *parent = nullptr);
};

class QueenWhite : public GUI::Piece
{
public:
    explicit QueenWhite(LOGIC::Color color, QWidget *parent = nullptr);
};

class KingWhite : public GUI::Piece
{
public:
    explicit KingWhite(LOGIC::Color color, QWidget *parent = nullptr);
};

}
#endif // GUI_WHITEPIECECLASSES_H

