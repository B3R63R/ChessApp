#ifndef BLACKPIECECLASSES_H
#define BLACKPIECECLASSES_H
#include "piece.h"
class pawnBlack : public piece
{
public:
    pawnBlack(QWidget *parent = 0);

};


class rookBlack : public piece
{
public:
    rookBlack(QWidget *parent = 0);
};

class knightBlack : public piece
{
public:
    knightBlack(QWidget *parent = 0);
};

class bishopBlack : public piece
{
public:
    bishopBlack(QWidget *parent = 0);
};

class queenBlack : public piece
{
public:
    queenBlack(QWidget *parent = 0);
};

class kingBlack : public piece
{
public:
    kingBlack(QWidget *parent = 0);
};

#endif // BLACKPIECECLASSES_H
