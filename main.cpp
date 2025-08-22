#include "mainwindow.h"
#include "startmenu.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/fonts/Cardot-nAal4.otf");
    a.setWindowIcon(QIcon(":/images/img/piecesicon.svg"));
    StartMenu w;
    w.show();
    return a.exec();
}


