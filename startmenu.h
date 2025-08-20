#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>

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

    void on_startButton_clicked();

private:
    void setStartButton();
    Ui::StartMenu *ui;

};

#endif // STARTMENU_H
