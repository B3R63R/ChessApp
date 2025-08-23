#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui_whitepiececlasses.h"
#include "gui_blackpiececlasses.h"
#include "gui_moveindicator.h"
#include <QLayout>
#include <QDebug>
#include <QList>
#include <algorithm>
#include "gui_moveindicator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    board.setupPieces();
    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);
    ui->gridLayout->setSpacing(0);
    //reverseBoard();
    setupSquaresColors();
    setupSquaresParameters();
    setupLabelParameters();
    setupBoardBorder();
    setupPieces();
    //handleCheck();
    handleGameStatus();
    if (ui->centralwidget->layout()) {
        ui->centralwidget->layout()->setAlignment(ui->frame, Qt::AlignCenter);
    }
    // ----------------------

    ui->gridLayout->setContentsMargins(0, 0, 0, 0);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameData;
}

int convertColCharToIntIdx(char col) {
    return col - 'A';
}

char convertColIntToCharIdx(int col) {
    return col + 'A';
}

int convertRowCharToIntIdx(char row) {
    return row - 1 - '0';
}

char convertRowIntToCharIdx(int row) {
    return row + 1 + '0';
}

void disconnectAllChildren(QObject *parent) {

    QList<QObject *> children = parent->findChildren<QObject *>();

    for (QObject *child : children) {
        child->disconnect();
    }
}

void MainWindow::swapGridWidgets(int row1, int col1, int row2, int col2) {

    auto item1 = ui->gridLayout->takeAt(ui->gridLayout->indexOf(ui->gridLayout->itemAtPosition(row1, col1)));
    auto item2 = ui->gridLayout->takeAt(ui->gridLayout->indexOf(ui->gridLayout->itemAtPosition(row2, col2)));

    ui->gridLayout->addItem(item1, row2, col2);
    ui->gridLayout->addItem(item2, row1, col1);
}

void MainWindow::reverseBoard() {

    int size = 8;
    int halfSize = size / 2;

    for (int row = 0; row < halfSize; row++) {
        for (int col = 1; col <= size; col++) {
            //skip first col for labels - (col = 1)
            //skip last row for labels - (size -1)
            swapGridWidgets(row, col, size -1 - row, size-col+1);
        }
    }

    //Change position labels
    for (int col = 0; col < halfSize; col++) {

        //Rows
        swapGridWidgets(col, 0, size - 1 - col, 0);

        //Columns
        swapGridWidgets(size, col+1, size, size - col);
    }

}

void MainWindow::handleGameStatus() {
    gameData = new GUI::GameData();
    connect(gameData, &GUI::GameData::moveMadeChanged, this, [=, this]() {

        //return {isEndgame, isCheckmate, isChecked, pieceColor, kingRow, kingCol};
        std::tuple<bool, bool, bool, char, int, int> gameStatus = board.examineGameStatus();

        bool isEndgame = std::get<0>(gameStatus);
        bool isCheckmate = std::get<1>(gameStatus);
        bool isChecked = std::get<2>(gameStatus);
        char pieceColor = std::get<3>(gameStatus);


        //Handle endgame
        if (isEndgame) disconnectAllChildren(ui->frame);

        // handle check
        if (isChecked) {
            int kingRowInt = std::get<4>(gameStatus);
            int kingColInt = std::get<5>(gameStatus);
            char kingRowChar = convertRowIntToCharIdx(kingRowInt);
            char kingColChar = convertColIntToCharIdx(kingColInt);
            std::string kingSquareName = "frame_" + std::string(1, kingColChar) + std::string(1,kingRowChar);
            auto kingSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(kingSquareName));
            if (isCheckmate) {
                kingSquare->setStyleSheet("background-color: #8C1D18;");
            }
            else {
                kingSquare->setStyleSheet("background-color: #D4AF37;");
            }
            gameData->lastKingSquareName =kingSquareName;
        }
        else {
            if (!(gameData->lastKingSquareName.empty())) {
                auto kingSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(gameData->lastKingSquareName));

                int row = convertRowIntToCharIdx(gameData->lastKingSquareName[7]);
                int col = convertColCharToIntIdx(gameData->lastKingSquareName[6]);

                updateSquareColor(kingSquare, row, col);
                gameData->lastKingSquareName.clear();

            }
        }


    });

}

void MainWindow::clearIndicators() {
    QList<GUI::MoveIndicator*> indicators = findChildren<GUI::MoveIndicator*>();
    for (auto indicator : indicators) {
        indicator->deleteLater();
    }
}

void MainWindow::handleTransferRookWhenCastling() {
    std::tuple<bool, char, int> castlingData = board.getIsCastling();
    if (std::get<0>(castlingData)) {

        char rowRookInt = std::get<2>(castlingData);
        int colRookInt = (std::get<1>(castlingData) == 'l') ? 0 : 7;
        int newColRookInt = (std::get<1>(castlingData) == 'l') ? 3 : 5;

        char rookRowChar = convertRowIntToCharIdx(rowRookInt);
        char rookColChar = convertColIntToCharIdx(colRookInt);
        char newRookColChar = convertColIntToCharIdx(newColRookInt);

        std::string rookSquareName = "frame_" + std::string(1, rookColChar) + std::string(1,rookRowChar);
        auto rookSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(rookSquareName));
        auto rook = rookSquare->findChild<GUI::Piece*>();
        std::string newRookSquareName = "frame_" + std::string(1, newRookColChar) + std::string(1,rookRowChar);
        auto newRookSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(newRookSquareName));

        rookSquare->layout()->removeWidget(rook);
        newRookSquare->layout()->addWidget(rook);
        rook->setCurrentFrame(newRookSquare);
    }
}

void MainWindow::handleEmptySquareMove(int row, int col) {
    //Download available moves
    std::vector<std::tuple<int,int>> availableMovesStorage = board.RaisePiece(row, col);
    availableMovesHistory = availableMovesStorage;

    //Show new indicators
    for (auto& [row, col] : availableMovesStorage) {

        //Convert data types
        char rowChar = convertRowIntToCharIdx(row);
        char colChar = convertColIntToCharIdx(col);

        //Create full objectName
        std::string squareName = "frame_" + std::string(1, colChar) + std::string(1,rowChar);

        //Access frame by objectName
        auto targetSquare = ui->frame->findChild<QFrame*>(squareName);

        //Check if square is empty
        auto targetSquarePiece = targetSquare->findChild<GUI::Piece*>();

        if (targetSquarePiece) {
            continue;
        }

        //Load indicator
        GUI::MoveIndicator *mIndicator = new GUI::MoveIndicator(targetSquare);
        targetSquare->layout()->addWidget(mIndicator);  
        //targetSquare->layout()->setAlignment(mIndicator, Qt::AlignCenter);

        //handling move on empty square
        connect(mIndicator, &QPushButton::clicked, this, [=, this]() {

            //Clear indicators from board

            auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
            auto targetSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(squareName));

            if (!lastPieceSquareClicked || !targetSquare) return;

            GUI::Piece* lastPiece = lastPieceSquareClicked->findChild<GUI::Piece*>();
            if (!lastPiece) return;

            //Raise piece from board
            lastPieceSquareClicked->layout()->removeWidget(lastPiece);

            //Place raised piece on new square
            targetSquare->layout()->addWidget(lastPiece);
            lastPiece->setCurrentFrame(targetSquare);
            //Update logic program
            board.makeLegalMove(lastRowClicked, lastColClicked, row, col);
            board.display();
            gameData->setMoveMade();
            handleTransferRookWhenCastling();

            clearIndicators();

            lastClickedPieceSquareName.clear();
            lastRowClicked = -1;
            lastColClicked = -1;
            availableMovesHistory.clear();
        });

    }

}

int MainWindow::handleBeatingMove(int row, int col, std::string fieldName) {

    clearIndicators();

    auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
    auto currentPieceSquareClicked = ui->frame->findChild<QFrame*>(fieldName);
    auto lastPiece = lastPieceSquareClicked->findChild<GUI::Piece*>();
    if (!lastPiece) {
        qDebug() << "lastPiece null";
        return 0;
    }
    auto currentPiece = currentPieceSquareClicked->findChild<GUI::Piece*>();
    if (!lastPieceSquareClicked || !currentPieceSquareClicked) return 0;
    lastPieceSquareClicked->layout()->removeWidget(lastPiece);
    if (currentPiece) {
        //delete taken piece
        currentPieceSquareClicked->layout()->removeWidget(currentPiece);
        currentPiece->deleteLater();
    }
    //add piece to new square
    currentPieceSquareClicked->layout()->addWidget(lastPiece);
    lastPiece->setCurrentFrame(currentPieceSquareClicked);

    //update logic program
    board.makeLegalMove(lastRowClicked, lastColClicked, row, col);

    gameData->setMoveMade();
    lastClickedPieceSquareName.clear();
    lastRowClicked = -1;
    lastColClicked = -1;
    return 0;
}


int MainWindow::handlePieceClick(const std::string& fieldName) {
    //Download coordinates
    int rowIdx = convertRowCharToIntIdx(fieldName[7]);
    int colIdx = convertColCharToIntIdx(fieldName[6]);
    std::tuple<int, int> move = {rowIdx, colIdx};
    const auto& piece = board.getBoard()[rowIdx][colIdx];

    //protection from nullptr
    if (!piece) return 0;

    //Check if it right color to move
    if ((piece->getColor() == "w" && !board.getIsWhiteTurn()) ||
        (piece->getColor() == "b" && board.getIsWhiteTurn())) {

        if (availableMovesHistory.empty()) {
            return 0;
            }
            //Beating
            else {
                if (std::find(availableMovesHistory.begin(), availableMovesHistory.end(), move) != availableMovesHistory.end()) {
                    handleBeatingMove(rowIdx, colIdx, fieldName);
                    board.display();
                }
                return 0;
            }

    }
    //Clear previous indicators from board
    clearIndicators();

    //Set variables to store last click history
    lastClickedPieceSquareName = fieldName;
    lastRowClicked = rowIdx;
    lastColClicked = colIdx;

    handleEmptySquareMove(rowIdx, colIdx);

    return 0;

}

void MainWindow::setPiece(QFrame *frame, GUI::Piece *piece) {

    frame->layout()->addWidget(piece);
    piece->setCurrentFrame(frame);
    connect(piece, &QPushButton::clicked, this, [=, this]() {

        handlePieceClick(piece->getCurrentFrame()->objectName().toStdString());

    });
}

GUI::Piece* MainWindow::choosePiece(char color, char pieceType, QFrame *frame) {
    if (color == 'w') {
        switch (pieceType) {
        case 'R':   return new GUI::RookWhite(frame);
        case 'N':   return new GUI::KnightWhite(frame);
        case 'B':   return new GUI::BishopWhite(frame);
        case 'Q':   return new GUI::QueenWhite(frame);
        case 'K':   return new GUI::KingWhite(frame);
        case 'P':   return new GUI::PawnWhite(frame);
        }
    } else { // BLACK
        switch (pieceType) {
        case 'R':   return new GUI::RookBlack(frame);
        case 'N':   return new GUI::KnightBlack(frame);
        case 'B':   return new GUI::BishopBlack(frame);
        case 'Q':   return new GUI::QueenBlack(frame);
        case 'K':   return new GUI::KingBlack(frame);
        case 'P':   return new GUI::PawnBlack(frame);
        }
    }
    return nullptr;
};

void MainWindow::setupPieces() {

    QMap<char, char> piecesMap;
    //Key-column symbol, value-piece symbol
    //Craated for custom piece location;
    piecesMap['A'] = 'R';  piecesMap['H'] = 'R';
    piecesMap['B'] = 'N';  piecesMap['G'] = 'N';
    piecesMap['C'] = 'B';  piecesMap['F'] = 'B';
    piecesMap['D'] = 'Q';  piecesMap['E'] = 'K';

    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();

    for (auto *frame : SquaresStorage) {
        auto fieldName = frame->objectName().toStdString();
        char row = fieldName[7];
        char col = fieldName[6];
        char color;
        char pieceType;
        bool shouldCreatePiece = false;

        if (!fieldName.starts_with("frame_")) continue;

        //Pawns
        if (row == '2' || row == '7') {
            color = (row == '2') ? 'w' : 'b';
            pieceType = 'P';
            shouldCreatePiece = true;

        }
        //Other pieces
        else if (row == '1' || row == '8') {
            color = (row == '1') ? 'w' : 'b';
            pieceType = piecesMap[col];
            shouldCreatePiece = true;

        }

        if (shouldCreatePiece) {
            auto piece = choosePiece(color, pieceType, frame);
            setPiece(frame, piece);
        }
    }

}



void MainWindow::setupLabelParameters() {
    QList<QLabel*> labelsStorage = ui->frame->findChildren<QLabel*>();
    for (auto label : labelsStorage) {
        //label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(
                "font-family: 'CARDOT';"
                "font-size: 15pt;"
            "color: #EAEAEA;"
            "background-color: #151515;"   );

    }

}

void MainWindow::setupBoardBorder() {
    ui->frame->setStyleSheet("#frame {padding-top: 0.5; border: none;}");

    QString borderStyle = "1.5px solid #7f7f7f;";
    QList<QWidget*> widgetStorage = ui->frame->findChildren<QWidget*>();
    for (auto widget : widgetStorage) {

        int widgetIdx = ui->gridLayout->indexOf(widget);
        QString currentStyle = widget->styleSheet();
        QString style;
        if (widgetIdx == -1) continue;
        int row, col, _;
        ui->gridLayout->getItemPosition(widgetIdx,  &row, &col, &_, &_);

        //Left side
        if (col == 1 && row != 8) {
            style += "border-left: " + borderStyle;

        }
        //Right side
        if (col == 8 && row !=8) style += "border-right: " + borderStyle;


        if (row == 7) {
            if (col != 0) style += "border-bottom: " + borderStyle;
        }

        //Top side
        if (row == 0 && col != 0) style += "border-top: " + borderStyle;

        //Set style
        if (!style.isEmpty()) widget->setStyleSheet(currentStyle + style + "border-style: solid;");


    }

}

void MainWindow::setupSquaresParameters() {

    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    for (auto frame : SquaresStorage) {
        if (!frame->objectName().startsWith("frame_")) continue;
        if (!frame->layout()) {
            auto layout = new QVBoxLayout(frame);
            frame->setLayout(layout);
        }

    }


}

void MainWindow::updateSquareColor(QFrame* square, int row, int col)
{
    const QString whiteSquareColor = "background-color: #3d3d3d; border: none;";
    const QString blackSquareColor = "background-color: #7f7f7f; border: none;";
    //ASCII 'A' numerical value is 65.
    if ((row % 2) == (col % 2)) {
        square->setStyleSheet(blackSquareColor);
    } else {
        square->setStyleSheet(whiteSquareColor);
    }
}

void MainWindow::setupSquaresColors() {
    QList<QFrame*> chessSquaresList = ui->frame->findChildren<QFrame*>();
    for (auto frame : chessSquaresList) {
        QString frameName= frame->objectName();

        int col = int(frameName.toStdString()[6]);
        int row = int(frameName.toStdString()[7]);

        updateSquareColor(frame, row, col);
    }
}



