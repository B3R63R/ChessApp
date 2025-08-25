#include "startmenu.h"
#include "ui_startmenu.h"
#include "mainwindow.h"
#include "startmenu.h"
#include <QIcon>
#include <QMenu>


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


    //Audio
    aStartGame = new QSoundEffect(this);
    aStartGame->setSource(QUrl("qrc:/sounds/sounds/game-start.wav"));
    aStartGame->setVolume(VOLUME);

    aClick = new QSoundEffect(this);
    aClick->setSource(QUrl("qrc:/sounds/sounds/click.wav"));
    aClick->setVolume(VOLUME);


}

StartMenu::~StartMenu()
{
    delete ui;
}


void StartMenu::setStartButton() {
    //QFont fontCardot("CARDOT", 32);
    auto* startButton = ui->pushButton_start;

}

void StartMenu::on_pushButton_start_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    aStartGame->play();
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

void StartMenu::on_pushButton_options_clicked()
{
    aClick->play();
}

