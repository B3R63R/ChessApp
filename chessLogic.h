#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H

#endif // CHESSLOGIC_H
#include <string>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <vector>
#include <tuple>

class Piece;

class Board {
public:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;

    Board();
    const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& getBoard() const;
    void display();
    void setupPieces();
    void setNewPosition(int currentRow, int currentCol, int newRow, int newCol);
    std::tuple<int, int> getKingLocation(std::string color) const;
};

class Piece {
public:
    std::string color;
    int row;
    int column;
    std::string name;
    bool hasMoved;

    Piece(const std::string& color, int row, int column, const std::string& name);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board, std::vector<std::tuple<int, int>>& directions);
    bool isAttackedBySlidingPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName);
    bool isAttackedByOtherPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName);
    bool isAttacked(const Board& board, int row, int col);
    bool isPinnedOrChecked( Board& board, int row, int col);
    std::string getSymbol();
    std::string getColor();
    std::string getName();
    int getColumn();
    int getRow();
    void setPosition(int Row, int Column);
    bool isMoved();
};

class Pawn : public Piece {
public:
    Pawn(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board);
};

class Knight : public Piece {
public:
    Knight(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board);
};

class Rook : public Piece {
public:
    Rook(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board);
};

class Bishop : public Piece {
public:
    Bishop(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board);
};

class Queen : public Piece {
public:
    Queen(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board);
};

class King : public Piece {
public:
    King(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board);
    bool isShortCastleAvailable(const Board& board);
};
