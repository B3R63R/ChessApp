#ifndef STARTMENU_H
#define STARTMENU_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QSoundEffect>
#include "optionswindow.h"

const double VOLUME = 0.2;

namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();


private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void on_pushButton_start_clicked();
    void on_pushButton_options_clicked();
    //void goToOptions();

private:
    void setStartButton();
    Ui::StartMenu *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* createMenuForTray();
    void clickSound();
    QSoundEffect* aClick;
    QSoundEffect* aStartGame;

};

#endif // STARTMENU_H
