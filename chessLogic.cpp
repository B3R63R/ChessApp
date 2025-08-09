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
            //Check if moves is in chessboard scope
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





