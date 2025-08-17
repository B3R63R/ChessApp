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
    std::array<int, 4> lastMove = {-1, -1, -1, -1};
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    bool isWhiteTurn;

    Board();

    void display();
    void setupPieces();
    void makeLegalMove(int currentRow, int currentCol, int newRow, int newCol);
    void setLastMove(int currentRow, int currentCol, int newRow, int newCol);
    void addPiece(int row, int col, std::string color, std::string name);
    bool getIsWhiteTurn();
    const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& getBoard() const;
    std::tuple<int, int> getKingLocation(std::string color) const;
    std::array<int, 4> getLastMove();
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& getBoardModifiable();
    std::vector<std::tuple<int,int>>RaisePiece(int currentRow, int currentCol);
    bool examineisKingChecked();
    bool examineCheckmate();



};

class Piece {
public:
    std::string color;
    int row;
    int column;
    std::string name;
    bool hasMoved;

    Piece(const std::string& color, int row, int column, const std::string& name);
    virtual std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) = 0;
    std::vector<std::tuple<int, int>> getPotentialMovesHelper(const Board& board, std::vector<std::tuple<int, int>>& directions);
    bool isAttackedBySlidingPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName);
    bool isAttackedByOtherPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName);
    bool isAttacked(const Board& board, int row, int col);
    bool CheckisKingInDanger( Board& board, int row, int col);
    virtual std::vector<std::tuple<int, int>> getAvailableMoves(Board& board);
    std::string getSymbol();
    std::string getColor();
    std::string getName();
    int getColumn();
    int getRow();
    void setPosition(int Row, int Column);
    bool getIsMoved();
    void setIsMoved();

};

class Pawn : public Piece {
public:
    Pawn(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Knight : public Piece {
public:
    Knight(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Rook : public Piece {
public:
    Rook(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Bishop : public Piece {
public:
    Bishop(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Queen : public Piece {
public:
    Queen(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class King : public Piece {
public:
    King(const std::string& color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;
    bool isShortCastleAvailable(const Board& board);
    bool isLongCastleAvailable(const Board& board);
    std::vector<std::tuple<int, int>> getAvailableMoves(Board& board) override;
};
