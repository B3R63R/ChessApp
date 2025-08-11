#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chessLogic.h"
#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    //void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *button=NULL;
    void setupSquaresColors();
    void setupSquaresParameters();
    void setupLabelParameters();
    void setupPiecesGUI();
};
#endif // MAINWINDOW_H
