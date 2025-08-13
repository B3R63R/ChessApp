#ifndef BLACKPIECECLASSES_H
#define BLACKPIECECLASSES_H
#include <QPushButton>

class pawnBlack : public QPushButton
{
public:
    pawnBlack(QWidget *parent = 0);
};


class rookBlack : public QPushButton
{
public:
    rookBlack(QWidget *parent = 0);
};

class knightBlack : public QPushButton
{
public:
    knightBlack(QWidget *parent = 0);
};

class bishopBlack : public QPushButton
{
public:
    bishopBlack(QWidget *parent = 0);
};

class queenBlack : public QPushButton
{
public:
    queenBlack(QWidget *parent = 0);
};

class kingBlack : public QPushButton
{
public:
    kingBlack(QWidget *parent = 0);
};

#endif // BLACKPIECECLASSES_H
