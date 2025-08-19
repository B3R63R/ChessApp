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
    startButton->setStyleSheet("border: none; "
                        "background-repeat: no-repeat; "
                        "background-position: center;"
                        "background-color: transparent;");

}

void StartMenu::on_startButton_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


