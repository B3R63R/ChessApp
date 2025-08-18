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
    reverseBoard();
    setupSquaresColors();
    setupSquaresParameters();
    setupLabelParameters();
    setupPiecesGUI();
    handleCheck();
    //auto *labelFrame1 = ui->gridLayout->itemAtPosition(0, 0)->widget();
    //auto label1 = labelFrame1->findChild<QLabel*>();
    //qDebug() << labelFrame1->objectName();

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

void MainWindow::reverseBoard() {

    for (int row = 0; row < 4; row++) {
        for (int col = 1; col < 9; col++) {

        auto *square1 = ui->gridLayout->itemAtPosition(row, col)->widget();
        ui->gridLayout->removeWidget(square1);

        auto *square2 = ui->gridLayout->itemAtPosition(7-row, col)->widget();
        ui->gridLayout->layout()->removeWidget(square2);
        ui->gridLayout->addWidget(square1, 7-row, col);
        ui->gridLayout->addWidget(square2, row, col);
        }
    }
    //Change position labels
    for (int i = 0; i < 4; i++) {
        //Rows
        auto *labelRow1 = ui->gridLayout->itemAtPosition(i, 0)->widget();
        auto *labelRow2 = ui->gridLayout->itemAtPosition(7-i, 0)->widget();
        ui->gridLayout->removeWidget(labelRow1);
        ui->gridLayout->removeWidget(labelRow2);
        ui->gridLayout->addWidget(labelRow1, 7-i, 0);
        ui->gridLayout->addWidget(labelRow2, i, 0);
        //Columns
        auto *labelCol1 = ui->gridLayout->itemAtPosition(8, i+1)->widget();
        auto *labelCol2 = ui->gridLayout->itemAtPosition(8, 8-i)->widget();
        ui->gridLayout->removeWidget(labelCol1);
        ui->gridLayout->removeWidget(labelCol2);
        ui->gridLayout->addWidget(labelCol1, 8, 8-i);
        ui->gridLayout->addWidget(labelCol2, 8, i+1);

    }
}

void MainWindow::updateSquareColor(QFrame* square, int row, int col)
{
    const QString whiteSquareColor = "background-color: lightgreen;";
    const QString blackSquareColor = "background-color: brown;";
    //ASCII 'A' numerical value is 65.
    if ((row % 2) == (col % 2)) {
        square->setStyleSheet(blackSquareColor);
    } else {
        square->setStyleSheet(whiteSquareColor);
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

void MainWindow::handleTrasferRookWhenCastling() {
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
        newRookSquare->layout()->setAlignment(rook, Qt::AlignCenter);
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
        targetSquare->layout()->setAlignment(mIndicator, Qt::AlignCenter);

        //handling move on empty square
        connect(mIndicator, &QPushButton::clicked, this, [=, this]() {

            //Clear indicators from board

            auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
            auto targetSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(squareName));

            if (!lastPieceSquareClicked || !targetSquare) return;

            GUI::Piece* lastPiece = lastPieceSquareClicked->findChild<GUI::Piece*>();
            if (!lastPiece) return;


            lastPieceSquareClicked->layout()->removeWidget(lastPiece);


            targetSquare->layout()->addWidget(lastPiece);
            targetSquare->layout()->setAlignment(lastPiece, Qt::AlignCenter);
            board.makeLegalMove(lastRowClicked, lastColClicked, row, col);
            gameData->setMoveMade();
            handleTrasferRookWhenCastling();

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
        currentPieceSquareClicked->layout()->removeWidget(currentPiece);
        currentPiece->deleteLater();
    }
    currentPieceSquareClicked->layout()->addWidget(lastPiece);
    currentPieceSquareClicked->layout()->setAlignment(lastPiece, Qt::AlignCenter);
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
    qDebug() << fieldName;

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
                    return 0;
                }

                else {
                    return 0;
                }
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


void MainWindow::setupPiecesGUI() {
    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();

    for (auto frame : SquaresStorage) {
        auto fieldName = frame->objectName().toStdString();
        char row = fieldName[7];
        char col = fieldName[6];
        if (fieldName[0] == 'f') {
            //Pawns
            if (row == '2') {

                GUI::PawnWhite *wPawn = new GUI::PawnWhite(frame);

                frame->layout()->addWidget(wPawn);
                frame->layout()->setAlignment(wPawn, Qt::AlignCenter);

                connect(wPawn, &QPushButton::clicked, this, [=, this]() {
                    QFrame* parentFrame = qobject_cast<QFrame*>(wPawn->parentWidget());
                    handlePieceClick(parentFrame->objectName().toStdString());
                });

            }
            else if (row == '7') {

                GUI::PawnBlack *bPawn = new GUI::PawnBlack(frame);

                frame->layout()->addWidget(bPawn);
                frame->layout()->setAlignment(bPawn, Qt::AlignCenter);

                connect(bPawn, &QPushButton::clicked, this, [=, this]() {
                    QFrame* parentFrame = qobject_cast<QFrame*>(bPawn->parentWidget());
                    handlePieceClick(parentFrame->objectName().toStdString());
                });

            }
            //Other pieces
            else if (row == '1') {
                //Set white
                if (col == 'A' || col == 'H' ) {
                    GUI::RookWhite *wRook = new GUI::RookWhite(frame);
                    frame->layout()->addWidget(wRook);
                    frame->layout()->setAlignment(wRook, Qt::AlignCenter);

                    connect(wRook, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wRook->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (col == 'B' || col == 'G') {
                    GUI::KnightWhite *wKnight = new GUI::KnightWhite(frame);
                    frame->layout()->addWidget(wKnight);
                    frame->layout()->setAlignment(wKnight, Qt::AlignCenter);

                    connect(wKnight, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wKnight->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (col == 'C' || col == 'F'){
                    GUI::BishopWhite*wBishop = new GUI::BishopWhite(frame);
                    frame->layout()->addWidget(wBishop);
                    frame->layout()->setAlignment(wBishop, Qt::AlignCenter);

                    connect(wBishop, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wBishop->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (col == 'D') {
                    GUI::QueenWhite *wQueen = new GUI::QueenWhite(frame);
                    frame->layout()->addWidget(wQueen);
                    frame->layout()->setAlignment(wQueen, Qt::AlignCenter);

                    connect(wQueen, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wQueen->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });

                }

                else if (col == 'E') {
                    GUI::KingWhite *wKing = new GUI::KingWhite(frame);
                    frame->layout()->addWidget(wKing);
                    frame->layout()->setAlignment(wKing, Qt::AlignCenter);

                    connect(wKing, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wKing->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });

                }
            }
            //Set black
            else if (row == '8') {

                if (col == 'A' || col == 'H' ) {
                    GUI::RookBlack *bRook = new GUI::RookBlack(frame);
                    frame->layout()->addWidget(bRook);
                    frame->layout()->setAlignment(bRook, Qt::AlignCenter);

                    connect(bRook, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bRook->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (col == 'B' || col == 'G') {
                    GUI::KnightBlack *bKnight = new GUI::KnightBlack(frame);
                    frame->layout()->addWidget(bKnight);
                    frame->layout()->setAlignment(bKnight, Qt::AlignCenter);

                    connect(bKnight, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bKnight->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (col == 'C' || col == 'F'){
                    GUI::BishopBlack *bBishop = new GUI::BishopBlack(frame);
                    frame->layout()->addWidget(bBishop);
                    frame->layout()->setAlignment(bBishop, Qt::AlignCenter);

                    connect(bBishop, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bBishop->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (col == 'D') {
                    GUI::QueenBlack *bQueen = new GUI::QueenBlack(frame);
                    frame->layout()->addWidget(bQueen);
                    frame->layout()->setAlignment(bQueen, Qt::AlignCenter);

                    connect(bQueen, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bQueen->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }

                else if (col == 'E') {
                    GUI::KingBlack *bKing = new GUI::KingBlack(frame);
                    frame->layout()->addWidget(bKing);
                    frame->layout()->setAlignment(bKing, Qt::AlignCenter);

                    connect(bKing, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bKing->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });

                }
            }

        }

    }

}

void MainWindow::setupLabelParameters() {
    QList<QLabel*> labelsStorage = ui->frame->findChildren<QLabel*>();
    for (auto label : labelsStorage) {
        label->setStyleSheet("background-color: white;");

    }
}

void MainWindow::setupSquaresParameters() {
    ui->frame->setMinimumSize(660,660);
    ui->frame->setMaximumSize(960,960);
    for (std::size_t i = 0; i<9; i++ ) {
        ui->gridLayout->setRowMinimumHeight(i, 85);
        ui->gridLayout->setColumnMinimumWidth(i, 85);
    }
    ui->gridLayout->setRowMinimumHeight(8, 35);
    ui->gridLayout->setColumnMinimumWidth(0, 35);

    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    for (auto frame : SquaresStorage) {
       if (!frame->layout()) {
           auto layout = new QVBoxLayout(frame);
           frame->setLayout(layout);
       }
    }

}

void MainWindow::setupSquaresColors() {
    QList<QFrame*> chessSquaresList = ui->frame->findChildren<QFrame*>();
    for (auto frame : chessSquaresList) {
        frame->setStyleSheet("background-color: lightgreen;");
        QString frameName= frame->objectName();

        int col = int(frameName.toStdString()[6]);
        int row = int(frameName.toStdString()[7]);

        updateSquareColor(frame, row, col);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

    QMainWindow::resizeEvent(event);
    //Access window size
    int w = ui->centralwidget->width();
    int h = ui->centralwidget->height();

    //Check which smaller
    int side = qMin(w, h);

    // Oblicz pozycję (x, y), aby wyśrodkować kwadrat w oknie
    int x = (w - side) / 2;
    int y = (h - side) / 2;

    // Ustaw nową geometrię dla ramki z szachownicą
    ui->frame->setGeometry(x, y, side, side);
}



