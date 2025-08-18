#include "chesslogic.h"
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>
//#include <QDebug>

LOGIC::Piece::Piece(const std::string& color, int row, int column, const std::string& name)
    : color(color), row(row), column(column), name(name), hasMoved(false) {}

std::string LOGIC::Piece::getSymbol() {
    return color+name;
}
std::string LOGIC::Piece::getColor() {
    return color;
}
std::string LOGIC::Piece::getName() {
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
bool LOGIC::Piece::isAttackedBySlidingPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName) {
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
                    return true;
                }

            }
        }
    }
    return false;
}
bool LOGIC::Piece::isAttackedByOtherPieces(const Board& board, int row, int col, std::vector<std::tuple<int, int>>& directions, const std::string& pieceName) {
    const auto& boardArray = board.getBoard();
    int direction;
    std::string opponentColor;

    //iterate directions
    for (const auto& [rowOffset, colOffset] : directions) {
        int examinedRow = row;
        int examinedCol = col;

        //If king is white look for black attacking pawn
        if (this->getColor() == "w") {
            opponentColor = "b";
            direction = 1;
        }
        else {
            opponentColor = "w";
            direction = -1;
        }
        //Check danger from king or knight
        if (pieceName == "K" || pieceName == "N") {
            examinedRow += rowOffset;
            examinedCol += colOffset;
        }
        //Check danger from pawns
        else if (pieceName == "P") {
            examinedRow += rowOffset * direction;
            examinedCol += colOffset;
        }
        //Check if move is in chessboard scope
        if (0 <= examinedRow && examinedRow < 8 && 0 <= examinedCol && examinedCol < 8) {
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

    bool isKingAttackedByRook = this->isAttackedBySlidingPieces(board, row, col, rookDirections, "R");
    bool isKingAttackedByBishop = this->isAttackedBySlidingPieces(board, row, col, bishopDirections, "B");
    bool isKingAttackedByPawn = this->isAttackedByOtherPieces(board, row, col, pawnDirections, "P");
    bool isKingAttackedByKnight = this->isAttackedByOtherPieces(board, row, col, knightDirections, "N");
    bool isKingAttackedByKing = this->isAttackedByOtherPieces(board, row, col, kingDirections, "K");

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
bool LOGIC::Piece::CheckisKingInDanger(Board& board, int row, int col) {

    auto& boardArray = board.getBoardModifiable();
    int currentRow = this->getRow();
    int currentCol = this->getColumn();

    //Keep piece that can be captured
    auto capturedPiece = std::move(boardArray[row][col]);

    //Place piece to new field
    std::string transferedPieceColor = boardArray[currentRow][currentCol]->getColor();
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

        if (this->CheckisKingInDanger(board, row, col) != true) {
            availableMoves.push_back({row, col});
        }
    }
    return availableMoves;
}

LOGIC::Pawn::Pawn(const std::string& color, int row, int column):
    Piece(color, row, column, "P") {}
std::vector<std::tuple<int, int>> LOGIC::Pawn::getPotentialMoves(const Board& board) {
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
            newCol = this->getColumn() + col;
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

            //Check beating piece diagonally (squere occupied by diffrent color piece)
            else if (boardArray[newRow][newCol] != nullptr && boardArray[newRow][newCol]->getColor() != this->getColor() && newCol != this->getColumn()) {
                potentialMoves.push_back({newRow, newCol});
            }
        }
    }
    return potentialMoves;

}



LOGIC::Knight::Knight(const std::string& color, int row, int column):
    Piece(color, row, column, "N") {}

std::vector<std::tuple<int, int>> LOGIC::Knight::getPotentialMoves(const Board& board) {
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



LOGIC::Rook::Rook(const std::string& color, int row, int column):
    Piece(color, row, column, "R") {}

std::vector<std::tuple<int, int>> LOGIC::Rook::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> rookDirections = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    return LOGIC::Piece::getPotentialMovesHelper(board, rookDirections);
}

LOGIC::Bishop::Bishop(const std::string& color, int row, int column):
    Piece(color, row, column, "B") {}

std::vector<std::tuple<int, int>> LOGIC::Bishop::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> bishopDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    return LOGIC::Piece::getPotentialMovesHelper(board, bishopDirections);
}
LOGIC::Queen::Queen(const std::string& color, int row, int column):
    Piece(color, row, column, "Q") {}

std::vector<std::tuple<int, int>> LOGIC::Queen::getPotentialMoves(const Board& board) {
    std::vector<std::tuple<int, int>> QueenDirections = {{1,1}, {1,-1}, {-1,1}, {-1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1}};
    return LOGIC::Piece::getPotentialMovesHelper(board, QueenDirections);
}

LOGIC::King::King(const std::string& color, int row, int column):
    Piece(color, row, column, "K") {}

std::vector<std::tuple<int, int>> LOGIC::King::getPotentialMoves(const Board& board) {
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

bool LOGIC::King::isShortCastleAvailable(const Board& board) {
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
    std::tuple<int, int> castlingFieldsStorage[3] = {currentKingField, passKingField, desiredKingField};

    //King didnt moved
    if (boardArray[kingRow][kingCol]->getIsMoved() || kingCol != 4) {
        return false;
    }

    //Rook have to have specific location
    if (boardArray[rookRow][rookCol] == nullptr || boardArray[rookRow][rookCol]->getName() != "R" || boardArray[rookRow][rookCol]->getColor() != this->getColor()) {
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
    if (this->getColor() == "w") {
        rookRow = 0;
    }
    else {
        rookRow = 7;
    }
    std::tuple currentKingField = {kingRow, kingCol};
    std::tuple passKingField = {kingRow, kingCol-1};
    std::tuple desiredKingField = {kingRow, kingCol-2};
    std::tuple passRookField = {kingRow, kingCol-3};
    std::tuple<int, int> castlingFieldsStorage[4] = {currentKingField, passKingField, desiredKingField, passRookField};

    //King didnt moved
    if (boardArray[kingRow][kingCol]->getIsMoved() || kingCol != 4) {
        return false;
    }
    //Rook have to have specific location
    if (boardArray[rookRow][rookCol] == nullptr || boardArray[rookRow][rookCol]->getName() != "R" || boardArray[rookRow][rookCol]->getColor() != this->getColor()) {
        return false;
    }
    //Castling fields must be empty
    if (boardArray[kingRow][kingCol-1] != nullptr || boardArray[kingRow][kingCol-2] != nullptr) {
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
    for (int row=0; row<8; row++) {
        for (int col = 0; col <8; col++) {
            board[row][col] = nullptr;
        }
    }
}
const std::array<std::array<std::unique_ptr<LOGIC::Piece>, 8>, 8>& LOGIC::Board::getBoard() const {
    return board;
}

void LOGIC::Board::display() {
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <8; col++) {
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

std::tuple<int,int> LOGIC::Board::getKingLocation(std::string color) const {
    int kingRow = -1;
    int kingCol = -1;
    size_t rowIdx = 0;
    const auto& boardArray = this->getBoard();
    for (const auto& row : boardArray) {
        size_t colIdx = 0;
        for (const auto& col : row) {
            if (col && col->getName() == "K" && col->getColor() == color) {
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

std::array<int, 4> LOGIC::Board::getLastMove() {
    return lastMove;
}

std::tuple<bool, char, int> LOGIC::Board::getIsCastling() {
    return isCastling;
}

void LOGIC::Board::setIsCastling(bool detector, char type, int row) {
    isCastling = {detector, type, row};
}


void LOGIC::Board::makeLegalMove(int currentRow, int currentCol, int newRow, int newCol) {

    auto& boardArr = getBoardModifiable();

    if (!boardArr[currentRow][currentCol]) {
        return;
    }
    auto& piece = boardArr[currentRow][currentCol];
    std::vector<std::tuple<int,int>> availableMovesForPiece = boardArr[currentRow][currentCol]->getAvailableMoves(*this);
    std::tuple<int, int> newMove = {newRow, newCol};

    bool isNewMoveInAvailableMoves = (std::find(availableMovesForPiece.begin(), availableMovesForPiece.end(), newMove) != availableMovesForPiece.end());

    bool detectorForCatling = false;
    char typeOfCastling = ' ';
    int row = -1;
    if (isNewMoveInAvailableMoves) {


        this->setLastMove(currentRow, currentCol, newRow, newCol);
        boardArr[newRow][newCol] = std::move(boardArr[currentRow][currentCol]);
        auto& movedPiece = boardArr[newRow][newCol];

        if (movedPiece) {
            movedPiece->setPosition(newRow, newCol);
            movedPiece->setIsMoved();
        }

        //Handle castling
        if (movedPiece->getName() == "K" && abs(newCol-currentCol) >1) {
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

void LOGIC::Board::addPiece(int row, int col, std::string color, std::string name) {
    if (name == "R") {
        // Wieża (Rook)
        board[row][col] = std::make_unique<Rook>(color, row, col);
    }
    else if (name == "N") {
        // Skoczek (Knight)
        board[row][col] = std::make_unique<Knight>(color, row, col);
    }
    else if (name == "B") {
        // Goniec (Bishop)
        board[row][col] = std::make_unique<Bishop>(color, row, col);
    }
    else if (name == "Q") {
        // Hetman (Queen)
        board[row][col] = std::make_unique<Queen>(color, row, col);
    }
    else if (name == "K") {
        // Król (King)
        board[row][col] = std::make_unique<King>(color, row, col);
    }
    else if (name == "P") {
        // Pion (Pawn)
        board[row][col] = std::make_unique<Pawn>(color, row, col);
    }

}

std::vector<std::tuple<int,int>> LOGIC::Board::RaisePiece(int currentRow, int currentCol) {
    auto const& piece = this->getBoard()[currentRow][currentCol];
    std::vector<std::tuple<int,int>> availableMovesForPiece = piece->getAvailableMoves(*this);
    return availableMovesForPiece;
}
std::array<std::array<std::unique_ptr<LOGIC::Piece>, 8>, 8>& LOGIC::Board::getBoardModifiable() {
    return board;
}

bool LOGIC::Board::getIsWhiteTurn() {
    return isWhiteTurn;
}
bool LOGIC::Board::examineisKingChecked() {
    auto& boardArr = this->getBoard();

    std::string kingColor = this->getIsWhiteTurn() ? "w" : "b";

    std::tuple<int, int> kingLocation = this->getKingLocation(kingColor);
    //protection when is isnt on board;
    if (std::get<0>(kingLocation) == -1) {
        return false;
    }
    //Check if king is exposed
    auto& king = boardArr[get<0>(kingLocation)][std::get<1>(kingLocation)];
    bool isKingInDanger = king->isAttacked(*this, std::get<0>(kingLocation), std::get<1>(kingLocation));
    return isKingInDanger;
}

bool LOGIC::Board::examineCheckmate() {
    std::string pieceColor = this->getIsWhiteTurn() ? "w" : "b";
    auto& boardArr = this->getBoard();

    for (auto& row : boardArr) {
        for (const auto& col : row) {
            if (col && col->getColor() == pieceColor) {
                if (!col->getAvailableMoves(*this).empty()) {
                    return false;
                }
            }
        }
    }
    return true;
}


/*
int main() {
    Board b;
    b.setupPieces();
    //b.addPiece(4, 3, "b", "R");
    //b.addPiece(5, 6, "b", "R");
    //b.addPiece(4, 6, "w", "K");
    b.addPiece(3, 6, "w", "K");
    b.addPiece(5, 6, "b", "P");
    b.display();

    //auto [row, col] = b.getKingLocation("w");

    //std::cout << "wiersz=" << row << ", kolumna=" << col << std::endl;

    for (const auto& t : b.getBoard()[1][0]->getAvailableMoves(b)) {
        std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ")\n";
    }
    b.makeLegalMove(1, 0, 2, 0);
    b.display();
    return 0;

}
*/





