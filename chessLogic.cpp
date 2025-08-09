#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <map>
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
public:
    Knight(const std::string& color, int row, int column):
        Piece(color, row, column, "N") {}
};


class Rook : public Piece {
public:
    Rook(const std::string& color, int row, int column):
        Piece(color, row, column, "R") {}
};

class Bishop : public Piece {
public:
    Bishop(const std::string& color, int row, int column):
        Piece(color, row, column, "B") {}
};

class Queen : public Piece {
public:
    Queen(const std::string& color, int row, int column):
        Piece(color, row, column, "Q") {}
};

class King : public Piece {
public:
    King(const std::string& color, int row, int column):
        Piece(color, row, column, "K") {}
};

class Board {
public:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    Board() {
        for (int row=0; row<8; row++) {
            for (int col = 0; col <8; col++) {
                board[row][col] = nullptr;
            }
        }
    }
    void display() {
        /*
        for (int row=0; row<8; row++) {
            for (int col = 0; col <8; col++) {
                if (board[row][col]) {
                    std::cout << board[row][col] -> getSymbol() + " ";
                }
                else {
                std::cout << "-";
                }
            }
            std::cout << '\n';
        }
        */

        for (int row = 7; row >= 0; row--) {
            for (int col = 0; col <8; col++) {
                if (board[row][col]) {
                    std::cout << board[row][col] -> getSymbol() + " ";
                }
                else {
                    std::cout << "-";
                }
            }
            std::cout << '\n';
        }
    }
    void setupPieces() {
        //Pawns
        for (int field = 0; field<8; field++) {
            board[1][field] = std::make_unique<Pawn>("w", 1, field);
            board[6][field] = std::make_unique<Pawn>("b", 6, field);

        }
        //Other pieces

        std::map <std::string, int> piecesParams = {{"w", 0}, {"b", 7}};

        for (auto itr = piecesParams.begin(); itr !=piecesParams.end(); itr++) {
            board[itr->second][0] = std::make_unique<Rook>(itr->first, itr->second, 0);
            board[itr->second][1] = std::make_unique<Knight>(itr->first, itr->second, 1);
            board[itr->second][2] = std::make_unique<Bishop>(itr->first, itr->second, 2);
            board[itr->second][3] = std::make_unique<Queen>(itr->first, itr->second, 3);
            board[itr->second][4] = std::make_unique<King>(itr->first, itr->second, 4);
            board[itr->second][5] = std::make_unique<Bishop>(itr->first, itr->second, 5);
            board[itr->second][6] = std::make_unique<Knight>(itr->first, itr->second, 6);
            board[itr->second][7] = std::make_unique<Rook>(itr->first, itr->second, 7);
        }
    }
};
int main() {
    Board b;
    b.setupPieces();
    b.display();
    return 0;
}





