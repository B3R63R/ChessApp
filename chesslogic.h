#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H


#include <string>
#include <vector>
#include <array>
#include <memory>
#include <tuple>

const int BOARD_SIZE = 8;

const int SHORT_CASTLE_ROOK_COL = 5;
const int LONG_CASTLE_ROOK_COL = 3;

const int WHITE_PIECES_HOME_ROW = 0;
const int BLACK_PIECES_HOME_ROW = 7;

const int WHITE_PAWNS_HOME_ROW = 1;
const int BLACK_PAWNS_HOME_ROW = 6;

namespace LOGIC {

enum class Color { WHITE, BLACK};
enum class PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

class Piece;

class Board {

public:

    Board();
    void display();
    void setupPieces();
    void makeLegalMove(int currentRow, int currentCol, int newRow, int newCol);
    void setLastMove(int currentRow, int currentCol, int newRow, int newCol);
    void addPiece(int row, int col, Color color, PieceType name);
    bool getIsWhiteTurn();
    void setIsWhiteTurn(bool setter);
    bool isInsideBoard(int row, int col) const;
    void setIsCastling(bool detector, char type, int row);
    const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& getBoard() const;
    std::tuple<int, int> getKingLocation(Color color) const;
    std::array<int, 4> getLastMove() const;
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& getBoardModifiable();
    std::vector<std::tuple<int,int>>RaisePiece(int currentRow, int currentCol);
    std::tuple<bool, int, int> examineKingCheck();
    std::tuple<bool, bool, bool, LOGIC::Color, int, int> examineGameStatus();
    std::tuple<bool, char, int> getIsCastling();
    std::tuple<bool, int, int, int, int> getEnPassantInfo();
    void setEnPassantInfo(bool EnPassantAvailable, int newRowForPawn, int newColForPawn, int capturedPawnRow,  int capturedPawnCol);
    bool isPromotion(int newRow, int newCol, auto& boardArr);
    void removePawnForEnPassant(int newRow, int newCol, auto& boardArr);
    void handleCastling(int newCol, int currentCol, auto& boardArr, auto& movedPiece);
    void setKingLocation(int row, int col, Color);


private:
    bool isWhiteTurn;
    std::tuple<bool, int, int, int, int> EnPassantInfo = {false, -1, -1, -1, -1};
    std::array<int, 4> lastMove = {-1, -1, -1, -1};
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    std::tuple<bool, char, int> isCastling;
    std::tuple<int, int> blackKingPos = {7, 4};
    std::tuple<int, int> whiteKingPos = {0, 4};


};

class Piece {
public:


    Piece(Color color, int row, int column, const PieceType name);
    virtual std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) = 0;
    std::vector<std::tuple<int, int>> getPotentialMovesHelper(const Board& board, std::vector<std::tuple<int, int>>& directions);
    bool isAttackedBySlidingPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, PieceType pieceName);
    bool isAttackedByOtherPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, PieceType pieceName);
    bool isAttacked(const Board& board, int row, int col);
    bool checkIfKingInDanger( Board& board, int row, int col);
    virtual std::vector<std::tuple<int, int>> getAvailableMoves(Board& board);
    std::string getSymbol();
    LOGIC::Color getColor();
    LOGIC::PieceType getName();
    int getColumn();
    int getRow();
    void setPosition(int Row, int Column);
    bool getIsMoved();
    void setIsMoved();
private:
    Color color;
    PieceType name;
    int row;
    int column;
    bool hasMoved;

};

class Pawn : public Piece {
public:
    Pawn(LOGIC::Color color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;
    std::array<int, 4> potentialEnPassant (const Board& board);
    std::tuple<int, int> handleEnPassant(Board& board);
    std::vector<std::tuple<int, int>> getAvailableMoves(Board& board) override;

};

class Knight : public Piece {
public:
    Knight(LOGIC::Color color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Rook : public Piece {
public:
    Rook(LOGIC::Color color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Bishop : public Piece {
public:
    Bishop(LOGIC::Color color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class Queen : public Piece {
public:
    Queen(LOGIC::Color color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;

};

class King : public Piece {
public:
    King(LOGIC::Color color, int row, int column);
    std::vector<std::tuple<int, int>> getPotentialMoves(const Board& board) override;
    bool isShortCastleAvailable(const Board& board);
    bool isLongCastleAvailable(const Board& board);
    std::vector<std::tuple<int, int>> getAvailableMoves(Board& board) override;
};
}
#endif // CHESSLOGIC_H
