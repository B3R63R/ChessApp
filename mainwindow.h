#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chesslogic.h"
#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include "gui_gamedata.h"
#include <QFrame>

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
    LOGIC::Board board;
    GUI::GameData *gameData;
    std::vector<std::tuple<int,int>> availableMovesHistory;
    std::string lastClickedPieceSquareName;
    int lastRowClicked;
    int lastColClicked;
    void setupSquaresColors();
    void setupSquaresParameters();
    void setupLabelParameters();
    void setupPiecesGUI();
    int handlePieceClick(const std::string& fieldName);
    int handleBeatingMove(int row, int col, std::string fieldName);
    void handleEmptySquareMove(int row, int col);
    void handleTrasferRookWhenCastling();
    void clearIndicators();
    void handleCheck();
    void updateSquareColor(QFrame* square, int row, int col);
    void reverseBoard();
};
#endif // MAINWINDOW_H
