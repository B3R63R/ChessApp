#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "whitepiececlasses.h"
#include "blackpiececlasses.h"
#include <QLayout>
#include <QDebug>

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

int convertRowCharIdxToRowIntIdx(char row) {
    int result;
    switch(row) {
    case 'A': {
        result = 1;
        break;
    }
    case 'B': {
        result = 2;
        break;
    }
    case 'C': {
        result = 3;
        break;
    }
    case 'D': {
        result = 4;
        break;
    }
    case 'E': {
        result = 5;
        break;
    }
    case 'F': {
        result = 6;
        break;
    }
    case 'G': {
        result = 7;
        break;
    }
    case 'H': {
        result = 8;
        break;
    }

    }
    return result;
}

void MainWindow::setupPiecesGUI() {
    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    //std::array<char, 8> rowIdx = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (auto frame : SquaresStorage) {
        auto fieldName = frame->objectName().toStdString();

        if (fieldName[0] == 'f') {
            //Pawns
            if (fieldName[7] == '2') {
                pawnWhite *wPawn = new pawnWhite(frame);
                frame->layout()->addWidget(wPawn);
                frame->layout()->setAlignment(wPawn, Qt::AlignCenter);
                //qDebug() << frame->objectName();
            }
            else if (fieldName[7] == '7') {
                pawnBlack *bPawn = new pawnBlack(frame);
                frame->layout()->addWidget(bPawn);
                frame->layout()->setAlignment(bPawn, Qt::AlignCenter);

                connect(bPawn, &QPushButton::clicked, this, [=]() {
                    char rowIdx = fieldName[7];
                    char colIdx = fieldName[6];
                    int irowIdx = (rowIdx - '0') -1;
                    int icolIdx = convertRowCharIdxToRowIntIdx(colIdx) -1;
                    board.RaisePiece(irowIdx, icolIdx);



                });

            }
            //Other pieces
            else if (fieldName[7] == '1') {
                //Set white
                if (fieldName[6] == 'A' || fieldName[6] == 'H' ) {
                    rookWhite *wRook = new rookWhite(frame);
                    frame->layout()->addWidget(wRook);
                    frame->layout()->setAlignment(wRook, Qt::AlignCenter);

                }
                else if (fieldName[6] == 'B' || fieldName[6] == 'G') {
                    knightWhite *wKnight = new knightWhite(frame);
                    frame->layout()->addWidget(wKnight);
                    frame->layout()->setAlignment(wKnight, Qt::AlignCenter);

                }
                else if (fieldName[6] == 'C' || fieldName[6] == 'F'){
                    bishopWhite *wBishop = new bishopWhite(frame);
                    frame->layout()->addWidget(wBishop);
                    frame->layout()->setAlignment(wBishop, Qt::AlignCenter);

                }
                else if (fieldName[6] == 'D') {
                    queenWhite *wQueen = new queenWhite(frame);
                    frame->layout()->addWidget(wQueen);
                    frame->layout()->setAlignment(wQueen, Qt::AlignCenter);

                }

                else if (fieldName[6] == 'E') {
                    kingWhite *wKing = new kingWhite(frame);
                    frame->layout()->addWidget(wKing);
                    frame->layout()->setAlignment(wKing, Qt::AlignCenter);

                }
            }
            //Set black
            else if (fieldName[7] == '8') {

                if (fieldName[6] == 'A' || fieldName[6] == 'H' ) {
                    rookBlack *bRook = new rookBlack(frame);
                    frame->layout()->addWidget(bRook);
                    frame->layout()->setAlignment(bRook, Qt::AlignCenter);

                }
                else if (fieldName[6] == 'B' || fieldName[6] == 'G') {
                    knightBlack *bKnight = new knightBlack(frame);
                    frame->layout()->addWidget(bKnight);
                    frame->layout()->setAlignment(bKnight, Qt::AlignCenter);

                }
                else if (fieldName[6] == 'C' || fieldName[6] == 'F'){
                    bishopBlack *bBishop = new bishopBlack(frame);
                    frame->layout()->addWidget(bBishop);
                    frame->layout()->setAlignment(bBishop, Qt::AlignCenter);

                }
                else if (fieldName[6] == 'D') {
                    queenBlack *bQueen = new queenBlack(frame);
                    frame->layout()->addWidget(bQueen);
                    frame->layout()->setAlignment(bQueen, Qt::AlignCenter);

                }

                else if (fieldName[6] == 'E') {
                    kingBlack *bKing = new kingBlack(frame);
                    frame->layout()->addWidget(bKing);
                    frame->layout()->setAlignment(bKing, Qt::AlignCenter);
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
        switch(frameName.toStdString()[6]) {
        case 'A':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            else {
                frame->setStyleSheet("background-color: brown;");
            }
            break;

        case 'B':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: brown;");
            }
            else {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            break;
        case 'C':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            else {
                frame->setStyleSheet("background-color: brown;");
            }
            break;
        case 'D':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: brown;");
            }
            else {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            break;
        case 'E':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            else {
                frame->setStyleSheet("background-color: brown;");
            }
            break;
        case 'F':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: brown;");
            }
            else {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            break;
        case 'G':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: lightgreen;");
            }
            else {
                frame->setStyleSheet("background-color: brown;");
            }
            break;


        case 'H':
            if (int(frameName.toStdString()[7]) % 2 == 0) {
                frame->setStyleSheet("background-color: brown;");
            }
            else {
                frame->setStyleSheet("background-color: lightgreen;");
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



