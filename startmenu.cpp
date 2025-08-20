#include "startmenu.h"
#include "ui_startmenu.h"
#include "mainwindow.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    setStartButton();
}

StartMenu::~StartMenu()
{
    delete ui;
}



void StartMenu::setStartButton() {
    QFont fontCardot("CARDOT", 32);
    auto* startButton = ui->startButton;
    startButton->setFont(fontCardot);
    ui->startButton->setStyleSheet(
        "QPushButton {"
        "font-family: 'CARDOT';"
        "font-size: 32pt;"
        "border: none;"
        "background-color: transparent;"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "}"

        "QPushButton:hover {"
        "    font-size: 36pt;"
        "}");

}

void StartMenu::on_startButton_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}
