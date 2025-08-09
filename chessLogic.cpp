#include <vector>
#include <string>
class Piece {
public:
    std::string color;
    int row;
    int column;
    std::string name;
    bool hasMoved;

    Piece(const std::string& color, int row, int column, const std::string& name):
        color(color), row(row), column(column), name(name), hasMoved(false) {}

    std::string getSymbol() {
        return color+name;
    }
    std::string getColor() {
        return color;
    }
    std::string getName() {
        return name;
    }
    int getColumn() {
        return column;
    }
    int getRow() {
        return row;
    }
    void setPosition(int Row, int Column) {
        row = Row;
        column = Column;
        hasMoved = true;
    }

};

class Pawn : public Piece {
public:
    Pawn(const std::string& color, int row, int column):
        Piece(color, row, column, "P") {}

};

class Knight : public Piece {
    Knight(const std::string& color, int row, int column):
        Piece(color, row, column, "N") {}
};


class Rook : public Piece {
    Rook(const std::string& color, int row, int column):
        Piece(color, row, column, "R") {}
};

class Bishop : public Piece {
    Bishop(const std::string& color, int row, int column):
        Piece(color, row, column, "B") {}
};

class Queen : public Piece {
    Queen(const std::string& color, int row, int column):
        Piece(color, row, column, "Q") {}
};

class King : public Piece {
    King(const std::string& color, int row, int column):
        Piece(color, row, column, "K") {}
};





