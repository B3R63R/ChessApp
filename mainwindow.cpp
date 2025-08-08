#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //setColors for squeres;

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->pushButton->move( rand() % 200, rand() % 200);

}

