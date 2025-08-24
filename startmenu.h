#ifndef STARTMENU_H
#define STARTMENU_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QSoundEffect>

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
    void on_startButton_clicked();
    //void goToOptions();


    void on_optionsButton_clicked();

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
