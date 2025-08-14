#ifndef WHITEPIECECLASSES_H
#define WHITEPIECECLASSES_H
#include <QPushButton>
#include "piece.h"


class pawnWhite : public piece
{
public:
    pawnWhite(QWidget *parent = 0);
};


class rookWhite : public piece
{
public:
    rookWhite(QWidget *parent = 0);
};

class knightWhite : public piece
{
public:
    knightWhite(QWidget *parent = 0);
};

class bishopWhite : public piece
{
public:
    bishopWhite(QWidget *parent = 0);
};

class queenWhite : public piece
{
public:
    queenWhite(QWidget *parent = 0);
};

class kingWhite : public piece
{
public:
    kingWhite(QWidget *parent = 0);
};

#endif // WHITEPIECECLASSES_H
