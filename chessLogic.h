#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H

#endif // CHESSLOGIC_H
#include <string>
#include <vector>
class Piece {
public:
    Piece(std::string color, int row, int column, std::string name);

    std::string getSymbol();

    std::string getColor();

    int getColum();

    int getRow();

    std::string getName();

    void setPosition();

    //virtual std::vector<std::pair<int,int>> getPotentialMoves(Board& board) = 0;
    //std::

};
