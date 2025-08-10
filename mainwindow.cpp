#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessLogic.h"
#include <QLayout>
#include <QDebug>
#include "pawnwhite.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->gridLayout->setSpacing(0);
    setupSquaresColors();
    setupSquaresParameters();

    pawnWhite *widget = new pawnWhite(ui->frame_A2);
    ui->frame_A2->layout()->addWidget(widget);
    ui->frame_A2->layout()->setAlignment(widget, Qt::AlignCenter);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSquaresParameters() {
   QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    for (auto frame : SquaresStorage) {
       frame->setMinimumSize(50, 50);
       frame->setMaximumSize(120, 120);

       if (!frame->layout()) {
           auto layout = new QHBoxLayout(frame);
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



