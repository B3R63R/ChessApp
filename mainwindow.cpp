#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui_whitepiececlasses.h"
#include "gui_blackpiececlasses.h"
#include "gui_moveindicator.h"
#include <QLayout>
#include <QDebug>
#include <QList>
#include <algorithm>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    board.setupPieces();
    board.display();
    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);
    ui->gridLayout->setSpacing(0);
    reverseBoard();
    setupSquaresColors();
    setupSquaresParameters();
    setupLabelParameters();
    setupBoardBorder();
    setupPieces();
    handleCheck();



}

MainWindow::~MainWindow()
{
    delete ui;
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
            qDebug() << row << ", " << col << " -> " << size -1 - row << ", " << size-col+1;
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

void MainWindow::handleCheck() {
    gameData = new GUI::GameData();
    connect(gameData, &GUI::GameData::moveMadeChanged, this, [=, this]() {
        if(board.examineisKingChecked()) {
            std::string kingColor = (board.getIsWhiteTurn()) ? "w" : "b";
            std::tuple<int, int> kingLocation = board.getKingLocation(kingColor);
            int kingRowInt = std::get<0>(kingLocation);
            int kingColInt = std::get<1>(kingLocation);
            char kingRowChar = convertRowIntToCharIdx(kingRowInt);
            char kingColChar = convertColIntToCharIdx(kingColInt);
            std::string kingSquareName = "frame_" + std::string(1, kingColChar) + std::string(1,kingRowChar);
            auto kingSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(kingSquareName));
            kingSquare->setStyleSheet("background-color: blue;");
            gameData->lastKingSquareName =kingSquareName;
            if (board.examineCheckmate()) {
                disconnectAllChildren(ui->frame);
            }
        }
        else {
            if (!(gameData->lastKingSquareName.empty())) {
                auto kingSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(gameData->lastKingSquareName));
                kingSquare->setStyleSheet("background-color: blue;");
                int row = int(gameData->lastKingSquareName[7]);
                int col = int(gameData->lastKingSquareName[6]);

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
    //Check if it right color to move

    if ((board.getBoard()[rowIdx][colIdx]->getColor() == "w" && !board.getIsWhiteTurn()) ||
        (board.getBoard()[rowIdx][colIdx]->getColor() == "b" && board.getIsWhiteTurn())) {

        if (availableMovesHistory.empty()) {
            return 0;
            }
            //Beating
            else {
                if (std::find(availableMovesHistory.begin(), availableMovesHistory.end(), move) != availableMovesHistory.end()) {
                    handleBeatingMove(rowIdx, colIdx, fieldName);
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
        //qDebug() << frame->objectName();
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

        label->setStyleSheet(
                "font-family: 'CARDOT';"
                "font-size: 15pt;"
            "color: #EAEAEA;"
            "background-color: #151515;"   );
    }

}

void MainWindow::setupBoardBorder() {
    ui->frame->setStyleSheet("#frame {padding-top: 0.5em; border: none;}");

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
        if (col == 0 && row != 8) {
            style += "border-right: " + borderStyle;

        }
        //right side
        if (col == 8 && row !=8) style += "border-right: " + borderStyle;


        if (row == 7) {
            if (col != 0) style += "border-bottom: " + borderStyle;
        }

        //bottom side
        //if (row == 8) style += "border-bottom: " + borderStyle;

        //top side
        if (row == 0 && col != 0) style += "border-top: " + borderStyle;


        if (!style.isEmpty()) {
            widget->setStyleSheet(currentStyle + style + "border-style: solid;");
        }
        /*
        //Left side
        if (col == 0) {
            style += (row == 8) ? "border-left: " + borderStyle :  "border-right: " + borderStyle + "border-left: " + borderStyle;

        }
        //right side
        if (col == 8) style += "border-right: " + borderStyle;


        if (row == 7) {
            if (col != 0) style += "border-bottom: " + borderStyle;
        }

        //bottom side
        if (row == 8) style += "border-bottom: " + borderStyle;

        //top side
        if (row == 0) style += "border-top: " + borderStyle;


        if (!style.isEmpty()) {
            widget->setStyleSheet(currentStyle + style + "border-style: solid;");
        }
        */
    }

}

void MainWindow::setupSquaresParameters() {
    ui->frame->setMinimumSize(660,660);
    ui->frame->setMaximumSize(960,960);

    int labelSize = 35;
    ui->gridLayout->setColumnMinimumWidth(0, labelSize);
    ui->gridLayout->setColumnStretch(0, 0);
    ui->gridLayout->setRowMinimumHeight(0, 85);
    ui->gridLayout->setRowStretch(0, 1);

    for (std::size_t i = 1; i<9; i++ ) {

        if (i == 8) {
            ui->gridLayout->setRowMinimumHeight(8, labelSize);
            ui->gridLayout->setRowStretch(8, 0);
            ui->gridLayout->setColumnStretch(i, 1);
            ui->gridLayout->setColumnMinimumWidth(i, 85);
            continue;
        }
        ui->gridLayout->setColumnStretch(i, 1);
        ui->gridLayout->setRowStretch(i, 1);

        ui->gridLayout->setRowMinimumHeight(i, 85);
        ui->gridLayout->setColumnMinimumWidth(i, 85);

    }


    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    for (auto frame : SquaresStorage) {
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int labelSize = 35;
    //Access window size
    int w = ui->centralwidget->width();
    int h = ui->centralwidget->height();
    //Check which smaller
    int side = qMin(w, h) - labelSize;
    side = (side/8)*8 + labelSize;
    // Calculate new position cords
    int x = (w - side) / 2;
    int y = (h - side) / 2;

    // Set new geometry
    ui->frame->setGeometry(x, y, side, side);
}


