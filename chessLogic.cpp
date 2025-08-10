#include "chessLogic.h"
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <tuple>

Piece::Piece(const std::string& color, int row, int column, const std::string& name)
    : color(color), row(row), column(column), name(name), hasMoved(false) {}

    std::string Piece::getSymbol() {
        return color+name;
    }
    std::string Piece::getColor() {
        return color;
    }
    std::string Piece::getName() {
        return name;
    }
    int Piece::getColumn() {
        return column;
    }
    int Piece::getRow() {
        return row;
    }
    void Piece::setPosition(int Row, int Column) {
        row = Row;
        column = Column;
        hasMoved = true;
    }
    bool Piece::isMoved() {
        return hasMoved;
    }
    std::vector<std::tuple<int, int>> Piece::getPotentialMoves(const Board& board, std::vector<std::tuple<int, int>>& directions) {
        std::vector<std::tuple<int, int>> potentialMoves;
        const auto& boardArray = board.getBoard();
        for (const auto& [rowOffset, colOffset] : directions) {
            int newRow = this->getRow();
            int newCol = this->getColumn();
            while(true) {
                newRow += rowOffset;
                newCol += colOffset;
                //Check if moves is in chessboard scope
                if (!(0 <= newRow && newRow < 8 && 0 <= newCol && newCol < 8)) {
                    break;
                }
                //Check moves to empty squeres
                else if (boardArray[newRow][newCol] == nullptr) {
                    potentialMoves.push_back({newRow, newCol});
                }
                //End loop if scanning reaches field with piece of the same color
                else if (boardArray[newRow][newCol]->getColor() == this->getColor()) {
                    break;
                }
                //Add take-piece-move and stop scanning at this direction
                else if (boardArray[newRow][newCol]->getColor() != this->getColor()) {
                    potentialMoves.push_back({newRow, newCol});
                    break;
                }
            }
        }
        return potentialMoves;
    }
    bool Piece::isAttackedBySlidingPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName) {
        const auto& boardArray = board.getBoard();
        bool pieceAttacked = false;
        //iterate directions
        for (const auto& [rowOffset, colOffset] : directions) {
            int examinedRow = row;
            int examinedCol = col;
            //scan direction
            while(true) {
                examinedRow += rowOffset;
                examinedCol += colOffset;
                //

                //Check if move is in chessboard scope
                if (!(0 <= examinedRow && examinedRow < 8 && 0 <= examinedCol && examinedCol < 8)) {
                    break;
                }
                //Field isn't attacked, check another field
                if (boardArray[examinedRow][examinedCol] == nullptr) {
                    continue;
                }
                //finish scanning direction if king is covered
                else if (boardArray[examinedRow][examinedCol]->getColor() == this->getColor() && boardArray[examinedRow][examinedCol]->getName() != "K") {
                    break;
                }
                //Scanner reached other color piece
                else if (boardArray[examinedRow][examinedCol]->getColor() != this->getColor()) {
                    //pointed piece attacks (or Queen) attacks king
                    if (boardArray[examinedRow][examinedCol]->getName() == pieceName || boardArray[examinedRow][examinedCol]->getName() == "Q") {
                        pieceAttacked = true;
                    }
                    //if other color piece doesn't endanger king
                    else {
                        break;
                    }
                }
            }
            if (pieceAttacked == true) {
                    break;
                }
        }
        return pieceAttacked;
    }
    bool Piece::isAttackedByOtherPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName) {
        const auto& boardArray = board.getBoard();
        bool pieceAttacked = false;
        //iterate directions
        for (const auto& [rowOffset, colOffset] : directions) {
            int examinedRow = row;
            int examinedCol = col;
            if (pieceName == "K" || pieceName == "N" || this->getColor() == "w") {
                examinedRow += rowOffset;
                examinedCol += colOffset;
            }
            else {
                examinedRow += rowOffset * (-1);
                examinedCol += colOffset;
            }
            //Check if move is in chessboard scope
            if (0 <= examinedRow && examinedRow < 8 && 0 <= examinedCol && examinedCol < 8) {
                //There is other color piece
                if (boardArray[examinedRow][examinedCol] != nullptr && boardArray[examinedRow][examinedCol]->getColor() != this->getColor()) {
                    //Check if this piece can attack king
                    if (boardArray[examinedRow][examinedCol]->getName() == pieceName) {
                        pieceAttacked = true;
                    }
                }
            }
        }
        return pieceAttacked;
    }
    bool Piece::isAttacked(const Board& board, int row, int col) {
        std::vector<std::tuple<int, int>> pawnDirections = {{1, 0 }, {2, 0}, {1, 1}, {1, -1}};
        std::vector<std::tuple<int, int>> knightDirections = {{1, 2}, {1, -2}, {2, 1}, {2, -1},{-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
        std::vector<std::tuple<int, int>> rookDirections = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        std::vector<std::tuple<int, int>> bishopDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
        std::vector<std::tuple<int, int>> kingDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};

        bool isKingAttackedByRook = this->isAttackedBySlidingPieces(board, row, col, rookDirections, "R");
        bool isKingAttackedByBishop = this->isAttackedBySlidingPieces(board, row, col, rookDirections, "B");
        bool isKingAttackedByPawn = this->isAttackedByOtherPieces(board, row, col, rookDirections, "P");
        bool isKingAttackedByKnight = this->isAttackedByOtherPieces(board, row, col, rookDirections, "N");
        bool isKingAttackedByKing = this->isAttackedByOtherPieces(board, row, col, rookDirections, "K");

        if (isKingAttackedByBishop) {
            return true;
        }
        else if (isKingAttackedByKnight) {
            return true;
        }
        else if (isKingAttackedByPawn) {
            return true;
        }

        else if (isKingAttackedByRook) {
            return true;
        }

        else if (isKingAttackedByKing) {
            return true;
        }
        else {
            return false;
        }


    }


Pawn::Pawn(const std::string& color, int row, int column):
    Piece(color, row, column, "P") {}

    std::vector<std::tuple<int, int>> Pawn::getPotentialMoves(const Board& board) {
        std::vector<std::tuple<int, int>> potentialMoves;
        const auto& boardArray = board.getBoard();
        std::vector<std::tuple<int, int>> pawnDirections = {{1, 0 }, {2, 0}, {1, 1}, {1, -1}};
        for (const auto& [row, col] : pawnDirections) {
            int newRow = 0;
            int newCol = 0;
            //Reject moves through 2 fields if pawn has moved
            if (row == 2 && this->hasMoved == true) {
                continue;
            }
            //Set directions based on current color
            if (this->color == "w") {
                newRow = this->getRow() + row;
                newCol = this->getColumn() + col;
            }
            else {
                newRow = this->getRow() + row*(-1);
                newCol = this->getColumn();
            }
            //Check if move is in chessboard scope
            if (0 <= newRow && newRow < 8 && 0 <= newCol && newCol < 8) {
                //Check moves on empty squere (the same column)
                if (boardArray[newRow][newCol] == nullptr && newCol == this->getColumn()) {
                    // move by one square
                    if (row != 2) {
                        potentialMoves.push_back({newRow, newCol});
                    }
                    //Check moves through 2 squares (indirect transition field must be empty)
                    else {
                        if (this->getColor() == "w") {
                            if (boardArray[newRow-1][newCol] == nullptr) {
                                potentialMoves.push_back({newRow, newCol});
                            }
                        }
                        else {
                            if (boardArray[newRow+1][newCol] == nullptr) {
                                potentialMoves.push_back({newRow, newCol});
                            }
                        }
                    }
                }
            }
            //Check beating piece diagonally (squere occupied by diffrent color piece)
            else if (boardArray[newRow][newCol] != nullptr && boardArray[newRow][newCol]->getColor() != this->getColor()) {
                potentialMoves.push_back({newRow, newCol});
            }
        }
        return potentialMoves;

    }


Knight::Knight(const std::string& color, int row, int column):
    Piece(color, row, column, "N") {}

    std::vector<std::tuple<int, int>> Knight::getPotentialMoves(const Board& board) {
        std::vector<std::tuple<int, int>> potentialMoves;
        const auto& boardArray = board.getBoard();
        std::vector<std::tuple<int, int>> knightDirections = {{1, 2}, {1, -2}, {2, 1}, {2, -1},
                                                            {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
        for (const auto& [row, col] : knightDirections) {
            int newRow = this->getRow() + row;
            int newCol = this->getColumn() + col;
            //Check if moves is in chessboard scope
            if (0 <= newRow && newRow < 8 && 0 <= newCol && newCol < 8) {
                //Move to empty square
                if (boardArray[newRow][newCol] == nullptr) {
                    potentialMoves.push_back({newRow, newCol});
                }
                //Take-piece-move
                else if (boardArray[newRow][newCol] != nullptr && boardArray[newRow][newCol]->getColor() != this->getColor()) {
                    potentialMoves.push_back({newRow, newCol});
                }
            }
        }
        return potentialMoves;
    }



Rook::Rook(const std::string& color, int row, int column):
    Piece(color, row, column, "R") {}

    std::vector<std::tuple<int, int>> Rook::getPotentialMoves(const Board& board) {
        std::vector<std::tuple<int, int>> rookDirections = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        return Piece::getPotentialMoves(board, rookDirections);
    }

Bishop::Bishop(const std::string& color, int row, int column):
    Piece(color, row, column, "B") {}

    std::vector<std::tuple<int, int>> Bishop::getPotentialMoves(const Board& board) {
        std::vector<std::tuple<int, int>> bishopDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
        return Piece::getPotentialMoves(board, bishopDirections);
    }
Queen::Queen(const std::string& color, int row, int column):
    Piece(color, row, column, "Q") {}

    std::vector<std::tuple<int, int>> Queen::getPotentialMoves(const Board& board) {
        std::vector<std::tuple<int, int>> QueenDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};
        return Piece::getPotentialMoves(board, QueenDirections);
    }

King::King(const std::string& color, int row, int column):
    Piece(color, row, column, "K") {}

    std::vector<std::tuple<int, int>> King::getPotentialMoves(const Board& board) {
        std::vector<std::tuple<int, int>> potentialMoves;
        const auto& boardArray = board.getBoard();
        std::vector<std::tuple<int, int>> kingDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};
        for (const auto& [row, col] : kingDirections) {
            int newRow = this->getRow() + row;
            int newCol = this->getColumn() + col;
            //Check if moves is in chessboard scope
            if (0 <= newRow && newRow < 8 && 0 <= newCol && newCol < 8) {
                //Move to empty square
                if (boardArray[newRow][newCol] == nullptr) {
                    potentialMoves.push_back({newRow, newCol});
                }
                //Take-piece-move
                else if (boardArray[newRow][newCol] != nullptr && boardArray[newRow][newCol]->getColor() != this->getColor()) {
                    potentialMoves.push_back({newRow, newCol});
                }
            }
        }
        return potentialMoves;
    }

    bool King::isShortCastleAvailable(const Board& board) {
        const auto& boardArray = board.getBoard();
        int kingRow = this->getRow();
        int kingCol = this->getColumn();
        int rookRow;
        int rookCol = 7;
        if (this->getColor() == "w") {
            rookRow = 0;
        }
        else {
            rookRow = 7;
        }
        std::tuple currentKingField = {kingRow, kingCol};
        std::tuple passKingField = {kingRow, kingCol+1};
        std::tuple desiredKingField = {kingRow, kingCol+2};

        //Castling fields must be empty
        if (boardArray[kingRow][kingCol+1] != nullptr || boardArray[kingRow][kingCol+2] != nullptr) {
            return false;
        }
        //Rook and King didnt moved
        if (boardArray[rookRow][rookCol]->isMoved())

        //Rook have to have specific location
        if (boardArray[rookRow][rookCol] == nullptr || boardArray[rookRow][rookCol]->getName() == "R" || boardArray[rookRow][rookCol]->getColor() != this->getColor()) {
            return false;
        }

        return true;
    }

Board::Board() {
    for (int row=0; row<8; row++) {
        for (int col = 0; col <8; col++) {
            board[row][col] = nullptr;
        }
    }
}
const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& Board::getBoard() const { //przenoszenie tylko do odczytu
    return board;
    }
void Board::display() {
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
void Board::setupPieces() {
    // Pawns
    for (int field = 0; field < 8; field++) {
        board[1][field] = std::make_unique<Pawn>("w", 1, field);
        board[6][field] = std::make_unique<Pawn>("b", 6, field);
    }

    // Other pieces
    std::map <std::string, int> piecesParams = {{"w", 0}, {"b", 7}};

    for (auto const& [color, row] : piecesParams) {
        board[row][0] = std::make_unique<Rook>(color, row, 0);
        board[row][1] = std::make_unique<Knight>(color, row, 1);
        board[row][2] = std::make_unique<Bishop>(color, row, 2);
        board[row][3] = std::make_unique<Queen>(color, row, 3);
        board[row][4] = std::make_unique<King>(color, row, 4);
        board[row][5] = std::make_unique<Bishop>(color, row, 5);
        board[row][6] = std::make_unique<Knight>(color, row, 6);
        board[row][7] = std::make_unique<Rook>(color, row, 7);
    }
}
int main() {
    Board b;
    b.setupPieces();
    b.display();
    return 0;
}





