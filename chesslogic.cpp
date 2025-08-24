#include "chesslogic.h"
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>


LOGIC::Piece::Piece(Color color, int row, int column, const PieceType name)
    : color(color), name(name), row(row), column(column), hasMoved(false) {}

std::string LOGIC::Piece::getSymbol() {
    std::string nameSymbol;
    std::string colorSymbol;

    if (this->getColor() == Color::WHITE) colorSymbol = "w";
    if (this->getColor() == Color::BLACK) colorSymbol = "b";

    switch (this->getName()) {

    case PieceType::PAWN:
        nameSymbol = "P";
        break;
    case PieceType::ROOK:
        nameSymbol = "R";
        break;
    case PieceType::KNIGHT:
        nameSymbol = "N";
        break;
    case PieceType::BISHOP:
        nameSymbol = "B";
        break;
    case PieceType::QUEEN:
        nameSymbol = "Q";
        break;
    case PieceType::KING:
        nameSymbol = "K";
        break;
    }
    return colorSymbol + nameSymbol;
}
LOGIC::Color LOGIC::Piece::getColor() {
    return color;
}
LOGIC::PieceType LOGIC::Piece::getName() {
    return name;
}
int LOGIC::Piece::getColumn() {
    return column;
}
int LOGIC::Piece::getRow() {
    return row;
}
void LOGIC::Piece::setPosition(int Row, int Column) {
    row = Row;
    column = Column;

}
bool LOGIC::Piece::getIsMoved() {
    return hasMoved;
}
void LOGIC::Piece::setIsMoved() {
    hasMoved = true;
}

std::vector<std::tuple<int, int>> LOGIC::Piece::getPotentialMovesHelper(const Board& board, std::vector<std::tuple<int, int>>& directions) {
    std::vector<std::tuple<int, int>> potentialMoves;
    const auto& boardArray = board.getBoard();
    for (const auto& [rowOffset, colOffset] : directions) {
        int newRow = this->getRow();
        int newCol = this->getColumn();
        while(true) {
            newRow += rowOffset;
            newCol += colOffset;
            //Check if moves is in chessboard scope
            if (!board.isInsideBoard(newRow, newCol)) {
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
bool LOGIC::Piece::isAttackedBySlidingPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, PieceType pieceName) {
    const auto& boardArray = board.getBoard();
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
            if (!(board.isInsideBoard(examinedRow, examinedCol))) {
                break;
            }
            //Field isn't attacked, check another field
            if (boardArray[examinedRow][examinedCol] == nullptr) {
                continue;
            }
            //finish scanning direction if king is covered by allies color pieces
            else if (boardArray[examinedRow][examinedCol]->getColor() == this->getColor()) {
                break;
            }

            //Scanner reached other color piece
            else if (boardArray[examinedRow][examinedCol]->getColor() != this->getColor()) {
                //pointed piece attacks (or Queen) attacks king
                if (boardArray[examinedRow][examinedCol]->getName() == pieceName || boardArray[examinedRow][examinedCol]->getName() == PieceType::QUEEN) {
                    return true;
                }
                //Enemy color covers king from danger
                else {
                    break;
                }

            }
        }
    }
    return false;
}
bool LOGIC::Piece::isAttackedByOtherPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const PieceType pieceName) {
    const auto& boardArray = board.getBoard();
    int direction;
    //Color opponentColor;

    //iterate directions
    for (const auto& [rowOffset, colOffset] : directions) {
        int examinedRow = row;
        int examinedCol = col;

        //If king is white look for black attacking pawn
        if (this->getColor() == Color::WHITE) {
            //opponentColor = Color::BLACK;
            direction = 1;
        }
        else {
            //opponentColor = Color::WHITE;
            direction = -1;
        }
        //Check danger from king or knight
        if (pieceName == PieceType::KING || pieceName == PieceType::KNIGHT) {
            examinedRow += rowOffset;
            examinedCol += colOffset;
        }
        //Check danger from pawns
        else if (pieceName == PieceType::PAWN) {
            examinedRow += rowOffset * direction;
            examinedCol += colOffset;
        }
        //Check if move is in chessboard scope
        if (board.isInsideBoard(examinedRow, examinedCol)) {
            //There is other color piece
            if (boardArray[examinedRow][examinedCol] != nullptr && boardArray[examinedRow][examinedCol]->getColor() != this->getColor()) {
                //Check if this piece can attack king
                if (boardArray[examinedRow][examinedCol]->getName() == pieceName) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool LOGIC::Piece::isAttacked(const Board& board, int row, int col) {
    std::vector<std::tuple<int, int>> pawnDirections = {{1, 1}, {1, -1}};
    std::vector<std::tuple<int, int>> knightDirections = {{1, 2}, {1, -2}, {2, 1}, {2, -1},{-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
    std::vector<std::tuple<int, int>> rookDirections = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    std::vector<std::tuple<int, int>> bishopDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    std::vector<std::tuple<int, int>> kingDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};

    bool isKingAttackedByRook = this->isAttackedBySlidingPieces(board, row, col, rookDirections, PieceType::ROOK);
    bool isKingAttackedByBishop = this->isAttackedBySlidingPieces(board, row, col, bishopDirections, PieceType::BISHOP);
    bool isKingAttackedByPawn = this->isAttackedByOtherPieces(board, row, col, pawnDirections, PieceType::PAWN);
    bool isKingAttackedByKnight = this->isAttackedByOtherPieces(board, row, col, knightDirections, PieceType::KNIGHT);
    bool isKingAttackedByKing = this->isAttackedByOtherPieces(board, row, col, kingDirections, PieceType::KING);

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
bool LOGIC::Piece::checkIfKingInDanger(Board& board, int row, int col) {

    auto& boardArray = board.getBoardModifiable();
    int currentRow = this->getRow();
    int currentCol = this->getColumn();

    //Keep piece that can be captured
    auto capturedPiece = std::move(boardArray[row][col]);

    //Place piece to new field
    Color transferedPieceColor = boardArray[currentRow][currentCol]->getColor();
    boardArray[row][col] = std::move(boardArray[currentRow][currentCol]);
    boardArray[row][col]->setPosition(row, col);

    //Check if king is exposed
    std::tuple<int, int> kingLocation = board.getKingLocation(transferedPieceColor);
    bool isKingInDanger = this->isAttacked(board, std::get<0>(kingLocation), std::get<1>(kingLocation));

    //Undo move to keep piece on their original place
    boardArray[currentRow][currentCol] = std::move(boardArray[row][col]);
    boardArray[currentRow][currentCol]->setPosition(currentRow, currentCol);

    //Restore captured piece
    boardArray[row][col] = std::move(capturedPiece);

    return isKingInDanger;
}

std::vector<std::tuple<int, int>> LOGIC::Piece::getAvailableMoves(Board& board) {
    std::vector<std::tuple<int, int>> potentialMovesStorage = this->getPotentialMoves(board);
    std::vector<std::tuple<int, int>> availableMoves;


    for (const auto& [row, col] : potentialMovesStorage) {

        if (this->checkIfKingInDanger(board, row, col) != true) {
            availableMoves.push_back({row, col});
        }
    }

    return availableMoves;
}

LOGIC::Pawn::Pawn(Color color, int row, int column):
    Piece(color, row, column, PieceType::PAWN) {}
//Piece(const std::string& colorSymbol, int row, int column, const std::string& nameSymbol, PieceType& name, Color& color);
std::vector<std::tuple<int, int>> LOGIC::Pawn::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> potentialMoves;
    const auto& boardArray = board.getBoard();
    std::vector<std::tuple<int, int>> pawnDirections = {{1, 0 }, {2, 0}, {1, 1}, {1, -1}};
    for (const auto& [row, col] : pawnDirections) {
        int newRow = 0;
        int newCol = 0;
        //Reject moves through 2 fields if pawn has moved
        if (row == 2 && this->getIsMoved() == true) {
            continue;
        }
        //Set directions based on current color
        if (this->getColor() == Color::WHITE) {
            newRow = this->getRow() + row;
            newCol = this->getColumn() + col;
        }
        else {
            newRow = this->getRow() + row*(-1);
            newCol = this->getColumn() + col;
        }
        //Check if move is in chessboard scope
        if (board.isInsideBoard(newRow, newCol)) {
            //Check moves on empty squere (the same column)
            if (boardArray[newRow][newCol] == nullptr && newCol == this->getColumn()) {
                // move by one square
                if (row != 2) {
                    potentialMoves.push_back({newRow, newCol});
                }
                //Check moves through 2 squares (indirect transition field must be empty)
                else {
                    if (this->getColor() == Color::WHITE) {
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

            //Check capture piece diagonally (squere occupied by diffrent color piece)
            else if (boardArray[newRow][newCol] != nullptr && boardArray[newRow][newCol]->getColor() != this->getColor() && newCol != this->getColumn()) {
                potentialMoves.push_back({newRow, newCol});
            }
        }
    }
    return potentialMoves;

}

std::array<int, 4> LOGIC::Pawn::potentialEnPassant (const Board& board) {

    int rowForPieceToMove = this->getRow();
    int colForPieceToMove = this->getColumn();
    auto& boardArr = board.getBoard();
    auto lastMove = board.getLastMove();
    int oldRowLastMove = lastMove[0];
    //int oldColLastMove = lastMove[1];
    int newRowLastMove = lastMove[2];
    int newColLastMove = lastMove[3];

    //If last move exists;
    if (newRowLastMove == -1) return {-1, -1, -1, -1};

    auto& lastPiece = boardArr[newRowLastMove][newColLastMove];
    auto& pieceToMove = boardArr[rowForPieceToMove][colForPieceToMove];

    //Check if pieces exist
    if (!lastPiece || !pieceToMove ) return {-1, -1, -1, -1};

    //Check if last piece moved was pawn
    if (lastPiece->getName() != PieceType::PAWN) return {-1, -1, -1, -1};

    //Check if it was move by 2 fields
    if (abs(newRowLastMove - oldRowLastMove) != 2) return {-1, -1, -1, -1};

    //Check if the same row
    if (newRowLastMove != rowForPieceToMove) return {-1, -1, -1, -1};

    //Check if is it close to the right or left then update enPassant col
    if (abs(colForPieceToMove - newColLastMove) == 1)

    colForPieceToMove = newColLastMove;

    //Need to know color to set row of enPassant
    rowForPieceToMove = (pieceToMove->getColor() == Color::WHITE) ? rowForPieceToMove+1 : rowForPieceToMove-1;
    //new square for pawn cords ; captured pawn cords
    return {rowForPieceToMove, colForPieceToMove, newRowLastMove, newColLastMove};

}

std::tuple<int, int> LOGIC::Pawn::handleEnPassant(Board& board) {

    auto enPassantInfo = this->potentialEnPassant(board);
    if (enPassantInfo[0] == -1) {
        board.setEnPassantInfo(false, -1, -1, -1, -1);
        return {-1, -1};
    }
    auto& boardArray = board.getBoardModifiable();
    int currentRow = this->getRow();
    int currentCol = this->getColumn();

    int newRowForPawn = enPassantInfo[0];
    int newColForPawn = enPassantInfo[1];

    int capturedPawnRow = enPassantInfo[2];
    int capturedPawnCol = enPassantInfo[3];

    //Store pawn that can be captured
    auto capturedPawn = std::move(boardArray[capturedPawnRow][capturedPawnCol]);

    Color transferedPieceColor = boardArray[currentRow][currentCol]->getColor();

    //Place piece to new field
    boardArray[newRowForPawn][newColForPawn] = std::move(boardArray[currentRow][currentCol]);
    boardArray[newRowForPawn][newColForPawn]->setPosition(newRowForPawn, newColForPawn);

    //Remove captured pawn
    boardArray[capturedPawnRow][capturedPawnCol] = nullptr;

    //Check if king is exposed
    std::tuple<int, int> kingLocation = board.getKingLocation(transferedPieceColor);
    bool EnPassantAvailable = !(this->isAttacked(board, std::get<0>(kingLocation), std::get<1>(kingLocation)));

    //Undo move to keep piece on their original place
    boardArray[currentRow][currentCol] = std::move(boardArray[newRowForPawn][newColForPawn]);
    boardArray[currentRow][currentCol]->setPosition(currentRow, currentCol);

    //Restore captured pawn
    boardArray[capturedPawnRow][capturedPawnCol] = std::move(capturedPawn);

    if (EnPassantAvailable) {
        board.setEnPassantInfo(EnPassantAvailable, newRowForPawn, newColForPawn, capturedPawnRow, capturedPawnCol);
        return {newRowForPawn, newColForPawn};
    }
    board.setEnPassantInfo(false, -1, -1, -1, -1);
    return {-1, -1};
}
std::vector<std::tuple<int, int>> LOGIC::Pawn::getAvailableMoves(Board& board) {

    auto availableMovesStorage =LOGIC::Piece::getAvailableMoves(board);
    auto enPassantMove = this->handleEnPassant(board);
    if (std::get<0>(enPassantMove) != -1) availableMovesStorage.push_back(enPassantMove);
    return availableMovesStorage;
}

LOGIC::Knight::Knight(Color color, int row, int column):
    Piece(color, row, column, PieceType::KNIGHT) {}

std::vector<std::tuple<int, int>> LOGIC::Knight::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> potentialMoves;
    const auto& boardArray = board.getBoard();
    std::vector<std::tuple<int, int>> knightDirections = {{1, 2}, {1, -2}, {2, 1}, {2, -1},
                                                          {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
    for (const auto& [row, col] : knightDirections) {
        int newRow = this->getRow() + row;
        int newCol = this->getColumn() + col;
        //Check if moves is in chessboard scope
        if (board.isInsideBoard(newRow, newCol)) {
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



LOGIC::Rook::Rook(Color color, int row, int column):
    Piece(color, row, column, PieceType::ROOK) {}

std::vector<std::tuple<int, int>> LOGIC::Rook::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> rookDirections = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    return LOGIC::Piece::getPotentialMovesHelper(board, rookDirections);
}

LOGIC::Bishop::Bishop(Color color, int row, int column):
    Piece(color, row, column, PieceType::BISHOP) {}

std::vector<std::tuple<int, int>> LOGIC::Bishop::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> bishopDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    return LOGIC::Piece::getPotentialMovesHelper(board, bishopDirections);
}
LOGIC::Queen::Queen(Color color, int row, int column):
    Piece(color, row, column, PieceType::QUEEN) {}

std::vector<std::tuple<int, int>> LOGIC::Queen::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> QueenDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};
    return LOGIC::Piece::getPotentialMovesHelper(board, QueenDirections);
}

LOGIC::King::King(Color color, int row, int column):
    Piece(color, row, column, PieceType::KING) {}

std::vector<std::tuple<int, int>> LOGIC::King::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> potentialMoves;
    const auto& boardArray = board.getBoard();
    std::vector<std::tuple<int, int>> kingDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};
    for (const auto& [row, col] : kingDirections) {
        int newRow = this->getRow() + row;
        int newCol = this->getColumn() + col;
        //Check if moves is in chessboard scope
        if (board.isInsideBoard(newRow, newCol)) {
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

bool LOGIC::King::isShortCastleAvailable(const Board& board) {
    const auto& boardArray = board.getBoard();
    int kingRow = this->getRow();
    int kingCol = this->getColumn();
    int rookRow;
    int rookCol = 7;
    if (this->getColor() == Color::WHITE) {
        rookRow = 0;
    }
    else {
        rookRow = 7;
    }
    std::tuple currentKingField = {kingRow, kingCol};
    std::tuple passKingField = {kingRow, kingCol+1};
    std::tuple desiredKingField = {kingRow, kingCol+2};
    std::tuple<int, int> castlingFieldsStorage[3] = {currentKingField, passKingField, desiredKingField};

    //King didnt moved
    if (boardArray[kingRow][kingCol]->getIsMoved() || kingCol != 4) {
        return false;
    }

    //Rook have to have specific location
    if (boardArray[rookRow][rookCol] == nullptr || boardArray[rookRow][rookCol]->getName() != PieceType::ROOK || boardArray[rookRow][rookCol]->getColor() != this->getColor()) {
        return false;
    }
    //Castling fields must be empty
    if (boardArray[kingRow][kingCol+1] != nullptr || boardArray[kingRow][kingCol+2] != nullptr) {
        return false;
    }
    //Rook didnt moved
    if (boardArray[rookRow][rookCol]->getIsMoved()) {
        return false;
    }
    //Castling fields are not attacked
    for (auto const& [row, col] : castlingFieldsStorage) {
        if (this->isAttacked(board, row, col)) {
            return false;
        }
    }
    return true;

}

bool LOGIC::King::isLongCastleAvailable(const Board& board) {
    const auto& boardArray = board.getBoard();
    int kingRow = this->getRow();
    int kingCol = this->getColumn();
    int rookRow;
    int rookCol = 0;
    if (this->getColor() == Color::WHITE) {
        rookRow = 0;
    }
    else {
        rookRow = 7;
    }
    std::tuple currentKingField = {kingRow, kingCol};
    std::tuple passKingField = {kingRow, kingCol-1};
    std::tuple desiredKingField = {kingRow, kingCol-2};
    std::tuple<int, int> castlingFieldsStorage[3] = {currentKingField, passKingField, desiredKingField};

    //King didnt moved
    if (boardArray[kingRow][kingCol]->getIsMoved() || kingCol != 4) return false;


    //Rook have to have specific location
    if (boardArray[rookRow][rookCol] == nullptr || boardArray[rookRow][rookCol]->getName() != PieceType::ROOK || boardArray[rookRow][rookCol]->getColor() != this->getColor()) {
        return false;
    }
    //Castling fields must be empty
    if (boardArray[kingRow][kingCol-1] != nullptr || boardArray[kingRow][kingCol-2] != nullptr) return false;

    //Rook didnt moved
    if (boardArray[rookRow][rookCol]->getIsMoved()) return false;

    //Castling fields are not attacked
    for (auto const& [row, col] : castlingFieldsStorage) {
        if (this->isAttacked(board, row, col)) {
            return false;
        }
    }
    return true;

}
std::vector<std::tuple<int, int>> LOGIC::King::getAvailableMoves(Board& board) {
    std::vector<std::tuple<int, int>> potentialMovesStorage = this->getPotentialMoves(board);
    bool isShortCastleAvailableResult = this->isShortCastleAvailable(board);
    bool isLongCastleAvailableResult = this->isLongCastleAvailable(board);
    int kingRow = this->getRow();
    int kingCol = this->getColumn();

    if (potentialMovesStorage.size() == 0) {
        return potentialMovesStorage;
    }
    std::vector<std::tuple<int, int>> availableMoves;
    //itarate potential moves
    for (auto const& [row, col] : potentialMovesStorage) {
        bool isKingAttackedResult = this->isAttacked(board, row, col);
        //Reject analized move (checking if move endanger king)
        if (isKingAttackedResult) {
            continue;
        }
        else {
            availableMoves.push_back({row, col});
        }
    }

    if (isShortCastleAvailableResult) {
        availableMoves.push_back({kingRow, kingCol+2});
    }
    if (isLongCastleAvailableResult) {
        availableMoves.push_back({kingRow, kingCol-2});
    }
    return availableMoves;
}

LOGIC::Board::Board() {
    isWhiteTurn = true;
    for (int row=0; row< BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = nullptr;
        }
    }
}
const std::array<std::array<std::unique_ptr<LOGIC::Piece>, BOARD_SIZE>, BOARD_SIZE>& LOGIC::Board::getBoard() const {
    return board;
}

void LOGIC::Board::display() {
    for (int row = BOARD_SIZE-1; row >= 0; row--) {
        for (int col = 0; col <BOARD_SIZE; col++) {
            if (board[row][col]) {
                std::cout << board[row][col] -> getSymbol() + " ";
            }
            else {
                std::cout << "--" << " ";
            }
        }

        std::cout << '\n';
    }
    std::cout << std::endl;
}

void LOGIC::Board::setupPieces() {

    // Pawns
    for (int field = 0; field < BOARD_SIZE; field++) {
        board[1][field] = std::make_unique<Pawn>(Color::WHITE, 1, field);
        board[6][field] = std::make_unique<Pawn>(Color::BLACK, 6, field);
    }

    // Other pieces
    std::map <LOGIC::Color, int> piecesParams = {{Color::WHITE, 0}, {Color::BLACK, 7}};

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

std::tuple<int,int> LOGIC::Board::getKingLocation(Color color) const {
    int kingRow = -1;
    int kingCol = -1;
    size_t rowIdx = 0;
    const auto& boardArray = this->getBoard();
    for (const auto& row : boardArray) {
        size_t colIdx = 0;
        for (const auto& piece : row) {
            if (piece && piece->getName() == PieceType::KING && piece->getColor() == color) {
                kingRow = rowIdx;
                kingCol = colIdx;
                return {kingRow, kingCol};
            }
            colIdx++;
        }
        rowIdx++;
    }
    return {-1, -1};
}
void LOGIC::Board::setLastMove(int currentRow, int currentCol, int newRow, int newCol) {
    lastMove[0] = currentRow;
    lastMove[1] = currentCol;
    lastMove[2] = newRow;
    lastMove[3] = newCol;
}

std::array<int, 4> LOGIC::Board::getLastMove() const{
    return lastMove;
}

std::tuple<bool, char, int> LOGIC::Board::getIsCastling() {
    return isCastling;
}

void LOGIC::Board::setIsCastling(bool detector, char type, int row) {
    isCastling = {detector, type, row};
}


void LOGIC::Board::makeLegalMove(int currentRow, int currentCol, int newRow, int newCol) {
    //Reset
    this->setIsCastling(false , ' ', -1);

    auto& boardArr = getBoardModifiable();

    auto& piece = boardArr[currentRow][currentCol];
    //if piece Exist
    if (!piece) return;

    std::vector<std::tuple<int,int>> availableMovesForPiece = piece->getAvailableMoves(*this);
    std::tuple<int, int> newMove = {newRow, newCol};

    bool isNewMoveInAvailableMoves = (std::find(availableMovesForPiece.begin(), availableMovesForPiece.end(), newMove) != availableMovesForPiece.end());

    bool detectorForCatling = false;
    char typeOfCastling = ' ';
    int row = -1;


    //Handle OtherMoves;
    if (isNewMoveInAvailableMoves) {

        this->setLastMove(currentRow, currentCol, newRow, newCol);
        boardArr[newRow][newCol] = std::move(boardArr[currentRow][currentCol]);
        auto& movedPiece = boardArr[newRow][newCol];

        if (movedPiece) {
            movedPiece->setPosition(newRow, newCol);
            movedPiece->setIsMoved();
        }

        //Handle EnPassant
        bool EnPassantAvailable = std::get<0>(this->EnPassantInfo);

        int newRowForPawn = std::get<1>(this->EnPassantInfo);
        int newColForPawn = std::get<2>(this->EnPassantInfo);

        int capturedPawnRow = std::get<3>(this->EnPassantInfo);
        int capturedPawnCol = std::get<4>(this->EnPassantInfo);

        if (EnPassantAvailable) {
            if (newRowForPawn == newRow && newColForPawn == newCol) boardArr[capturedPawnRow][capturedPawnCol] = nullptr;
        }

        //Handle castling
        if (movedPiece->getName() == PieceType::KING && abs(newCol-currentCol) >1) {
            row = isWhiteTurn ? 0 : 7;
            detectorForCatling = true;
            //Short castle
            if (newCol == 6) {
                boardArr[row][5] = std::move(boardArr[row][7]);
                auto& rook = boardArr[row][5];
                rook->setPosition(row, 5);
                rook->setIsMoved();
                typeOfCastling = 's';
            }
            //Long castle
            else {
                boardArr[row][3] = std::move(boardArr[row][0]);
                auto& rook = boardArr[row][3];
                rook->setPosition(row, 3);
                rook->setIsMoved();
                typeOfCastling = 'l';
            }
        }

        isWhiteTurn = !isWhiteTurn;
        this->setIsCastling(detectorForCatling, typeOfCastling, row);
    }
}

void LOGIC::Board::addPiece(int row, int col, Color color, PieceType name) {
    if (name == PieceType::ROOK) {
        //Rook
        board[row][col] = std::make_unique<Rook>(color, row, col);
    }
    else if (name == PieceType::KNIGHT) {
        //Knight
        board[row][col] = std::make_unique<Knight>(color, row, col);
    }
    else if (name == PieceType::BISHOP) {
        //Bishop
        board[row][col] = std::make_unique<Bishop>(color, row, col);
    }
    else if (name == PieceType::QUEEN) {
        //Queen
        board[row][col] = std::make_unique<Queen>(color, row, col);
    }
    else if (name == PieceType::KING) {
        //King
        board[row][col] = std::make_unique<King>(color, row, col);
    }
    else if (name == PieceType::PAWN) {
        //Pawn
        board[row][col] = std::make_unique<Pawn>(color, row, col);
    }

}

std::vector<std::tuple<int,int>> LOGIC::Board::RaisePiece(int currentRow, int currentCol) {
    auto const& piece = this->getBoard()[currentRow][currentCol];
    //Protection from nullptr
    if (!piece) return {};
    std::vector<std::tuple<int,int>> availableMovesForPiece = piece->getAvailableMoves(*this);
    return availableMovesForPiece;
}
std::array<std::array<std::unique_ptr<LOGIC::Piece>, BOARD_SIZE>, BOARD_SIZE>& LOGIC::Board::getBoardModifiable() {
    return board;
}

bool LOGIC::Board::getIsWhiteTurn() {
    return isWhiteTurn;
}
std::tuple<bool, int, int>LOGIC::Board::examineKingCheck() {
    auto& boardArr = this->getBoard();

    Color kingColor = this->getIsWhiteTurn() ? Color::WHITE : Color::BLACK;

    std::tuple<int, int> kingLocation = this->getKingLocation(kingColor);
    //protection when is isnt on board;
    if (std::get<0>(kingLocation) == -1) {
        return {false, -1, -1};
    }
    //Check if king is exposed
    auto& king = boardArr[std::get<0>(kingLocation)][std::get<1>(kingLocation)];
    int row = std::get<0>(kingLocation);
    int col = std::get<1>(kingLocation);
    bool isKingInDanger = king->isAttacked(*this, row, col);
    return {isKingInDanger, row, col};
}

std::tuple<bool, bool, bool, LOGIC::Color, int, int> LOGIC::Board::examineGameStatus() {

    auto& boardArr = this->getBoard();
    std::tuple<bool, int, int> kingCkeckInfo = this->examineKingCheck();
    bool isChecked = std::get<0>(kingCkeckInfo);
    int kingRow = std::get<1>(kingCkeckInfo);
    int kingCol = std::get<2>(kingCkeckInfo);
    bool isEndgame = true;
    bool isCheckmate = true;
    Color pieceColor = (this->getIsWhiteTurn()) ? Color::WHITE : Color::BLACK;

    for (auto& row : boardArr) {
        for (const auto& piece : row) {

            if (piece && piece->getColor() == pieceColor) {
                if (!piece->getAvailableMoves(*this).empty()) {
                    isEndgame = false;
                    isCheckmate = false;
                    return {isEndgame, isCheckmate, isChecked, pieceColor, kingRow, kingCol};
                }
            }
        }
    }
    return {isEndgame, isCheckmate, isChecked, pieceColor, kingRow, kingCol};

}

bool LOGIC::Board::isInsideBoard(int row, int col) const{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

std::tuple<bool, int, int, int, int> LOGIC::Board::getEnPassantInfo() {
    return EnPassantInfo;
}
//{EnPassantAvailable, newRowForPawn, newColForPawn, capturedPawnRow, capturedPawnCol}
void LOGIC::Board::setEnPassantInfo(bool EnPassantAvailable, int newRowForPawn, int newColForPawn, int capturedPawnRow,  int capturedPawnCol) {
    EnPassantInfo = {EnPassantAvailable, newRowForPawn, newColForPawn, capturedPawnRow, capturedPawnCol};
}
/*
int main() {
    LOGIC::Board b;
    b.setupPieces();
    //b.addPiece(4, 3, "b", "R");
    //b.addPiece(5, 6, "b", "R");
    //b.addPiece(4, 6, "w", "K");
    //b.addPiece(3, 6, "w", "K");
    //b.addPiece(5, 6, "b", "P");
    //b.display();

    //auto [row, col] = b.getKingLocation("w");

    //std::cout << "wiersz=" << row << ", kolumna=" << col << std::endl;

    for (const auto& t : b.getBoard()[1][0]->getAvailableMoves(b)) {
        std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ")\n";
    }

    b.makeLegalMove(1, 0, 2, 0);
    b.makeLegalMove(6, 0, 5, 0);
    b.makeLegalMove(2, 0, 3, 0);
    b.makeLegalMove(5, 0, 4, 0);
    b.display();
    return 0;

}
*/





