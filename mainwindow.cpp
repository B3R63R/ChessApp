#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pawnwhite.h"
#include <QLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Board b;
    b.setupPieces();
    b.display();

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

void MainWindow::setupPiecesGUI() {
    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    //std::array<char, 8> rowIdx = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (auto frame : SquaresStorage) {
        if (frame->objectName()[7] == '2' && frame->objectName()[0] == 'f') {
            pawnWhite *wPawn = new pawnWhite(frame);
            frame->layout()->addWidget(wPawn);
            frame->layout()->setAlignment(wPawn, Qt::AlignCenter);
            qDebug() << frame->objectName();
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

