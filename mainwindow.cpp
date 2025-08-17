#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "whitepiececlasses.h"
#include "blackpiececlasses.h"
#include "moveindicator.h"
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
    setupSquaresColors();
    setupSquaresParameters();
    setupLabelParameters();
    setupPiecesGUI();
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
        auto targetSquarePiece = targetSquare->findChild<piece*>();

        if (targetSquarePiece) {
            continue;
        }

        //Load indicator
        moveIndicator *mIndicator = new moveIndicator(targetSquare);
        targetSquare->layout()->addWidget(mIndicator);
        targetSquare->layout()->setAlignment(mIndicator, Qt::AlignCenter);

        //handling move on empty square
        connect(mIndicator, &QPushButton::clicked, this, [=, this]() {

            //Clear indicators from board

            auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
            auto targetSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(squareName));

            if (!lastPieceSquareClicked || !targetSquare) return;

            piece* lastPiece = lastPieceSquareClicked->findChild<piece*>();
            if (!lastPiece) return;


            lastPieceSquareClicked->layout()->removeWidget(lastPiece);


            targetSquare->layout()->addWidget(lastPiece);
            targetSquare->layout()->setAlignment(lastPiece, Qt::AlignCenter);

            board.makeLegalMove(lastRowClicked, lastColClicked, row, col);


            QList<moveIndicator*> indicators = findChildren<moveIndicator*>();
            for (auto indicator : indicators) {
                indicator->deleteLater();
            }


            lastClickedPieceSquareName.clear();
            lastRowClicked = -1;
            lastColClicked = -1;
            availableMovesHistory.clear();
        });

    }

}

int MainWindow::handleBeatingMove(int row, int col, std::string fieldName) {
    QList<moveIndicator*> indicators = findChildren<moveIndicator*>();
    for (auto indicator : indicators) {
        indicator->deleteLater();
    }

    auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
    auto currentPieceSquareClicked = ui->frame->findChild<QFrame*>(fieldName);
    auto lastPiece = lastPieceSquareClicked->findChild<piece*>();
    auto currentPiece = currentPieceSquareClicked->findChild<piece*>();
    if (!lastPieceSquareClicked || !currentPieceSquareClicked) return 0;
    lastPieceSquareClicked->layout()->removeWidget(lastPiece);
    if (currentPiece) {
        currentPieceSquareClicked->layout()->removeWidget(currentPiece);
        currentPiece->deleteLater();
    }
    currentPieceSquareClicked->layout()->addWidget(lastPiece);
    currentPieceSquareClicked->layout()->setAlignment(lastPiece, Qt::AlignCenter);
    board.makeLegalMove(lastRowClicked, lastColClicked, row, col);
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
                    return 0;
                }

                else {
                    return 0;
                }
            }

    }

    //Clear previous indicators from board
    QList<moveIndicator*> indicators = findChildren<moveIndicator*>();
    for (auto indicator : indicators) {
        indicator->deleteLater();
    }
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

        if (fieldName[0] == 'f') {
            //Pawns
            if (fieldName[7] == '2') {

                pawnWhite *wPawn = new pawnWhite(frame);

                wPawn->setPosition(1, convertColCharToIntIdx(fieldName[6]));
                frame->layout()->addWidget(wPawn);
                frame->layout()->setAlignment(wPawn, Qt::AlignCenter);

                connect(wPawn, &QPushButton::clicked, this, [=, this]() {
                    QFrame* parentFrame = qobject_cast<QFrame*>(wPawn->parentWidget());
                    handlePieceClick(parentFrame->objectName().toStdString());
                });

            }
            else if (fieldName[7] == '7') {

                pawnBlack *bPawn = new pawnBlack(frame);

                bPawn->setPosition(6, convertColCharToIntIdx(fieldName[6]));
                frame->layout()->addWidget(bPawn);
                frame->layout()->setAlignment(bPawn, Qt::AlignCenter);

                connect(bPawn, &QPushButton::clicked, this, [=, this]() {
                    QFrame* parentFrame = qobject_cast<QFrame*>(bPawn->parentWidget());
                    handlePieceClick(parentFrame->objectName().toStdString());
                });

            }
            //Other pieces
            else if (fieldName[7] == '1') {
                //Set white
                if (fieldName[6] == 'A' || fieldName[6] == 'H' ) {
                    rookWhite *wRook = new rookWhite(frame);
                    frame->layout()->addWidget(wRook);
                    frame->layout()->setAlignment(wRook, Qt::AlignCenter);

                    connect(wRook, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wRook->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (fieldName[6] == 'B' || fieldName[6] == 'G') {
                    knightWhite *wKnight = new knightWhite(frame);
                    frame->layout()->addWidget(wKnight);
                    frame->layout()->setAlignment(wKnight, Qt::AlignCenter);

                    connect(wKnight, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wKnight->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (fieldName[6] == 'C' || fieldName[6] == 'F'){
                    bishopWhite *wBishop = new bishopWhite(frame);
                    frame->layout()->addWidget(wBishop);
                    frame->layout()->setAlignment(wBishop, Qt::AlignCenter);

                    connect(wBishop, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wBishop->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (fieldName[6] == 'D') {
                    queenWhite *wQueen = new queenWhite(frame);
                    frame->layout()->addWidget(wQueen);
                    frame->layout()->setAlignment(wQueen, Qt::AlignCenter);

                    connect(wQueen, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wQueen->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });

                }

                else if (fieldName[6] == 'E') {
                    kingWhite *wKing = new kingWhite(frame);
                    frame->layout()->addWidget(wKing);
                    frame->layout()->setAlignment(wKing, Qt::AlignCenter);

                    connect(wKing, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(wKing->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });

                }
            }
            //Set black
            else if (fieldName[7] == '8') {

                if (fieldName[6] == 'A' || fieldName[6] == 'H' ) {
                    rookBlack *bRook = new rookBlack(frame);
                    frame->layout()->addWidget(bRook);
                    frame->layout()->setAlignment(bRook, Qt::AlignCenter);

                    connect(bRook, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bRook->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (fieldName[6] == 'B' || fieldName[6] == 'G') {
                    knightBlack *bKnight = new knightBlack(frame);
                    frame->layout()->addWidget(bKnight);
                    frame->layout()->setAlignment(bKnight, Qt::AlignCenter);

                    connect(bKnight, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bKnight->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (fieldName[6] == 'C' || fieldName[6] == 'F'){
                    bishopBlack *bBishop = new bishopBlack(frame);
                    frame->layout()->addWidget(bBishop);
                    frame->layout()->setAlignment(bBishop, Qt::AlignCenter);

                    connect(bBishop, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bBishop->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }
                else if (fieldName[6] == 'D') {
                    queenBlack *bQueen = new queenBlack(frame);
                    frame->layout()->addWidget(bQueen);
                    frame->layout()->setAlignment(bQueen, Qt::AlignCenter);

                    connect(bQueen, &QPushButton::clicked, this, [=, this]() {
                        QFrame* parentFrame = qobject_cast<QFrame*>(bQueen->parentWidget());
                        handlePieceClick(parentFrame->objectName().toStdString());
                    });


                }

                else if (fieldName[6] == 'E') {
                    kingBlack *bKing = new kingBlack(frame);
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

        const QString squareType_1 = "background-color: lightgreen;";
        const QString squareType_2 = "background-color: brown";

        switch(frameName.toStdString()[6]) {
        case 'A':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_1);
            }
            else {
                frame->setStyleSheet(squareType_2);
            }
            break;

        case 'B':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_2);
            }
            else {
                frame->setStyleSheet(squareType_1);
            }
            break;
        case 'C':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_1);
            }
            else {
                frame->setStyleSheet(squareType_2);
            }
            break;
        case 'D':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_2);
            }
            else {
                frame->setStyleSheet(squareType_1);
            }
            break;
        case 'E':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_1);
            }
            else {
                frame->setStyleSheet(squareType_2);
            }
            break;
        case 'F':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_2);
            }
            else {
                frame->setStyleSheet(squareType_1);
            }
            break;
        case 'G':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_1);
            }
            else {
                frame->setStyleSheet(squareType_2);
            }
            break;


        case 'H':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet(squareType_2);
            }
            else {
                frame->setStyleSheet(squareType_1);
            }
            break;
        }

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



