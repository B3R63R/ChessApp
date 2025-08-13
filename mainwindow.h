#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chesslogic.h"
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

private:
    Ui::MainWindow *ui;
    QPushButton *button=NULL;
    Board board;

    void setupSquaresColors();
    void setupSquaresParameters();
    void setupLabelParameters();
    void setupPiecesGUI();

};
#endif // MAINWINDOW_H
