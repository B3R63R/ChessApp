#include "startmenu.h"
#include "ui_startmenu.h"
#include "mainwindow.h"
#include "startmenu.h"
#include <QIcon>
StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)

{
    ui->setupUi(this);
    // Trey icon menu
    trayIcon = new QSystemTrayIcon(this);
    auto menu = this->createMenuForTray();
    this->trayIcon->setContextMenu(menu);

    //App icon
    auto appIcon = QIcon(":/images/img/piecesicon.png");

    this->trayIcon->setIcon(appIcon);
    this->setWindowIcon(appIcon);

    //Display tray
    this->trayIcon->show();

    // Interaction
    connect(trayIcon, &QSystemTrayIcon::activated, this, &StartMenu::iconActivated);


}

StartMenu::~StartMenu()
{
    delete ui;
}



void StartMenu::setStartButton() {
    QFont fontCardot("CARDOT", 32);
    auto* startButton = ui->startButton;

}

void StartMenu::on_startButton_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void StartMenu::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
    switch (reason_) {
    case QSystemTrayIcon::Trigger:
        this->trayIcon->showMessage("Hello", "You clicked me!");
        break;
    default:
        ;
    }
}

QMenu* StartMenu::createMenuForTray()
{
    // App can exit via Quit menu
    auto quitAction = new QAction("&Quit", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    auto menu = new QMenu(this);
    menu->addAction(quitAction);

    return menu;
}
